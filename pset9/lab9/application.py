import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

# Initialize a list of all possible values for month and day
months = list(range(1,13))
days = list(range(1,32))

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", request.form.get("name"), request.form.get("month"), request.form.get("day"))

        return redirect("/")

    else:

        data = db.execute("SELECT * FROM birthdays")
        # the total number of entries in the database
        entries = db.execute("SELECT COUNT(*) AS num FROM birthdays")[0]["num"]

        return render_template("index.html", months=months, days=days, bday_data=data, entries=entries)

@app.route("/delete_entry", methods=["POST"])
def delete_entry():
    # Identify which bin button was clicked to identify which entry is to be deleted
    bin_no =  int(request.form["bin_button"]) + 1
    db.execute("DELETE FROM birthdays WHERE id = ?", bin_no)

    # Once an entry is deleted, the order of the ids will get messed up. So delete all the entries and add them again to reorder all the entries
    data = db.execute("SELECT name, month, day FROM birthdays")
    db.execute("DELETE FROM birthdays")
    for row in data:
        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", row["name"], row["month"], row["day"])

    return redirect("/")