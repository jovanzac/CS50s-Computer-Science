-- Keep a log of any SQL queries you execute as you solve the mystery.


-- 1) Started out by finding the crime scene report from the table crime_scene_reports using the following command
SELECT * FROM crime_scene_reports WHERE month = 7 AND day = 28;


-- 2) Since the report mentioned witnesses, took a look at the interviews table
SELECT * FROM interviews
WHERE month = 7 AND day = 28;


-- 3) Ruth mentions a getaway car. So took a look at the courthouse footage
--    Got a bunch of license plates that left around the specified time
SELECT * FROM courthouse_security_logs
WHERE month = 7 AND day = 28 AND hour = 10;


-- 4) Eugene mentioned that the thief had withdrawn some money. So taking a look at the atm records
--    Got a list of all account numbers that were used that day to withdraw money
SELECT * FROM atm_transactions
WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street";


-- 5) Finally, Raymond mentions hearing the thief taking to someone over the phone about a flight ticket. Taking a look at all relavent flights
SELECT id FROM flights
WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") ORDER BY hour, minute LIMIT 1;


-- 6) We now know the flight id of the flight the thief used to escape. Looking at this flight's destination will tell us where the thief escaped to.
SELECT city FROM airports
WHERE id IN
(SELECT destination_airport_id FROM flights
WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") ORDER BY hour, minute LIMIT 1);
-- ==> THE THIEF ESCAPED TO LONDON


-- 7) Taking a look at all passengers in the specified flight
SELECT * FROM passengers
WHERE flight_id = (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") ORDER BY hour, minute LIMIT 1);


-- 8) Taking a look at all phone calls made that day that lasted less than a minute at 10
SELECT * FROM phone_calls
WHERE year = 2020 AND  month = 7 AND day = 28 AND duration < 60;


-- 9) Using the license plate data, the account transaction data, flight data and phone call logs to narrow down the list of suspects to a single one
SELECT people.name FROM people
JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
WHERE courthouse_security_logs.month = 7 AND courthouse_security_logs.day = 28 AND courthouse_security_logs.hour = 10 AND activity = "exit" AND minute BETWEEN 15 AND 25
INTERSECT
SELECT people.name FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.year = 2020 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = "Fifer Street" AND atm_transactions.transaction_type = "withdraw"
INTERSECT
SELECT people.name FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE phone_calls.year = 2020 AND  phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration < 60
INTERSECT
SELECT name FROM people
WHERE people.passport_number IN
(SELECT passport_number FROM passengers
WHERE flight_id = (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") ORDER BY hour, minute LIMIT 1));
-- ==> ERNEST IS THE THIEF


-- 10) Lastly we find out who the reciever at the end of Ernest's call was
SELECT people.name FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE phone_calls.caller = (SELECT phone_number FROM people WHERE name = "Ernest") AND year = 2020 AND  month = 7 AND day = 28 AND duration < 60;
-- ==> BERTHOLD IS THE ACCOMPLICE