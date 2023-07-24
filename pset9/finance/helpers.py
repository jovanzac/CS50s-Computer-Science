import os
import requests
import urllib.parse

from flask import redirect, render_template, request, session
from functools import wraps


def apology(message, code=400):
    """Render message as an apology to user."""
    def escape(s):
        """
        Escape special characters.
        """
        for old, new in [("-", "--"), (" ", "-"), ("_", "__"), ("?", "~q"),
                         ("%", "~p"), ("#", "~h"), ("/", "~s"), ("\"", "''")]:
            s = s.replace(old, new)
        return s
    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):
    """
    Decorate routes to require login.

    https://flask.palletsprojects.com/en/1.1.x/patterns/viewdecorators/
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function


def lookup(symbol):
    """Look up quote for symbol."""

    # Contact API
    sym = urllib.parse.quote_plus(symbol)
    try:
        api_key = os.environ.get("API_KEY")
        print(api_key)
        url_real_time = f"https://api.twelvedata.com/price?symbol={sym}&apikey={api_key}"
        price = requests.get(url_real_time)
        price.raise_for_status()
        url_quote = f"https://api.twelvedata.com/quote?symbol={sym}&apikey={api_key}"
        quote = requests.get(url_quote)
        print(f"url_quote: {quote}")
    except requests.RequestException:
        print("$"*30)
        print("Exception")
        return None

    # Parse response
    try:
        price = price.json()
        quote = quote.json()
        print(f"quote: {quote}")
        print(f"price: {price}")
        return {
            "name": quote["name"],
            "price": float(price["price"]),
            "symbol": sym
        }
    except (KeyError, TypeError, ValueError):
        return None


def usd(value):
    """Format value as USD."""
    return f"${value:,.2f}"
