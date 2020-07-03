import os
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import date, datetime

from helpers import apology, login_required, lookup, usd, complexity_check

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    ### Query DB for current users's cash balance
    rows = db.execute("SELECT * FROM users WHERE id = :id",
                        id=session["user_id"])
    
    cash = rows[0]["cash"]

    ### Query DB for current user's holdings
    rows = db.execute("SELECT * FROM holdings WHERE userid = :userid",
                        userid=session["user_id"])
    
    ### Loop through all of the current holdings to determine current value of each holding and current price of each holding
    holdings_info = []
    i = 0
    total_value = 0
    for row in rows:
        holding = {}

        symbol = rows[i]["symbol"]
        shares = rows[i]["shares"]

        lookup_response = lookup(symbol)
        price = lookup_response["price"]
        name = lookup_response["name"]

        value = shares * price
        total_value += value
        price = usd(price)
        value = usd(value)

        holding.update( {'symbol' : symbol} )
        holding.update( {'name' : name} )
        holding.update( {'shares' : shares} )
        holding.update( {'price' : price} )
        holding.update( {'value' : value} )

        holdings_info.append(holding)

        i += 1

    ### Calculate grand total (cash + stocks total value)
    total_value += cash
    total_value = usd(total_value)
    cash = usd(cash)

    ### return index.html
    return render_template("index.html", holdings_info=holdings_info, cash=cash, total_value=total_value)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":

        ### return buy.html, form to purchase a stock with fields for symbol and shares
        return render_template("buy.html")

    else:
        
        ### Ensure input was provided
        if not request.form.get("symbol"):
            return apology("must provide symbol")

        if not request.form.get("shares"):
            return apology("must provide number of shares")

        ### If shares is not a positive integer, send apology
        try:
            int(request.form.get("shares"))
        except ValueError:
            return apology("shares must be a whole number greater than 0")

        if int(request.form.get("shares")) < 0:
            return apology("shares must be a whole number greater than 0")

        ### Lookup the symbol
        symbol = request.form.get("symbol")
        lookup_response = lookup(symbol)

        ### If lookup returns none, send apology
        if lookup_response == None:
            return apology("invalid stock symbol")
        else:
            price = lookup_response["price"]
            symbol = lookup_response["symbol"]
            shares = int(request.form.get("shares"))

        ### Calculate total cost of all the shares requested
        total_cost = price * shares

        ### Query DB to ensure user has sufficient funds available
        rows = db.execute("SELECT * FROM users WHERE id = :id",
                            id=session["user_id"])

        if rows[0]["cash"] < total_cost:
            return apology("insufficient funds to purchase this stock")

        else:
        
            ### Query DB to see if this user already has shares of the requested symbol
            already_purchased = db.execute("SELECT * FROM holdings WHERE userid = :userid AND symbol = :symbol",
                                            userid=session["user_id"], symbol=symbol)
            
            ### If the user already has shares of the requested symbol, update that record in the DB to reflect the added shares
            if len(already_purchased) > 0:
                existing_shares = already_purchased[0]["shares"]
                shares += existing_shares
                db.execute("UPDATE holdings SET shares = :shares WHERE userid = :userid AND symbol = :symbol",
                                            shares=shares, userid=session["user_id"], symbol=symbol)
            
            ### If the user does not already have shares of that symbol, insert the purchase into the DB as a new record
            else:
                db.execute("INSERT INTO holdings (symbol, shares, userid) VALUES(:symbol, :shares, :userid)", symbol=symbol, shares=shares, userid=session["user_id"])
            
            ### Subtract the cost of the shares purchased from the user's cash, and update the DB with the new amount
            new_cash = rows[0]["cash"] - total_cost
            db.execute("UPDATE users SET cash=:new_cash WHERE id = :id",
                        new_cash=new_cash, id=session["user_id"])
            
            ### Update the history table with the transaction
            action = "Buy"
            today = date.today()
            now = datetime.now()
            day = today.strftime("%d/%m/%Y") 
            time = now.strftime("%H:%M:%S")

            db.execute("INSERT INTO history (userid, action, symbol, price, shares, date, time) VALUES(:userid, :action, :symbol, :price, :shares, :day, :time)",
                        userid=session["user_id"], action=action, symbol=symbol, price=price, shares=shares, day=day, time=time)

            ### Redirect user to home page
            return redirect("/")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    ### Query DB for current user's holdings
    transactions_info = db.execute("SELECT * FROM history WHERE userid = :userid",
                        userid=session["user_id"])
    
    ### Display history.html with table of all user transations
    return render_template("history.html", transactions_info=transactions_info)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":

        ### Display form to request stock quote
        return render_template("quote.html")

    else:
        
        ### Ensure input was provided
        if not request.form.get("symbol"):
            return apology("must provide symbol")

        ### Lookup stock symbol (lookup function)
        symbol = request.form.get("symbol")
        lookup_response = lookup(symbol)

        ### If lookup returns none, send apology
        if lookup_response == None:
            return apology("invalid stock symbol")
        else:
            name = lookup_response["name"]
            price = usd(lookup_response["price"])
            symbol = lookup_response["symbol"]

            return render_template("quoted.html", name=name, symbol=symbol, price=price)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":

        ### Return register form
        return render_template("register.html")

    else:
        ### Return apology if any field was blank
        if not request.form.get("username"):
            return apology("must provide username", 403)

        ### Ensure password was submitted
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("must provide password", 403)

        ### Confirm passwords match
        if not (request.form.get("password") == request.form.get("confirmation")):
            return apology("passwords must match", 403)

        ### Confirm username is free
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                            username=request.form.get("username"))
        if len(rows) > 0:
            return apology("that username is already taken", 403)

        else:

            ### Check password complexity
            if complexity_check(request.form.get("password")):

                ### hash password
                hash = generate_password_hash(request.form.get("password"))
                
            else:
                return apology("password complexity requirements not met. Password must be at least 8 characters long and contain at least 1 number and 1 letter", 403)

        ### Insert into users table in DB
        db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", username=request.form.get("username"), hash=hash)

        ### Redirect user to home page
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":

        ### return buy.html, form to purchase a stock with fields for symbol and shares
        return render_template("sell.html")

    else:
        
        ### Ensure input was provided
        if not request.form.get("symbol"):
            return apology("must provide symbol")

        if not request.form.get("shares"):
            return apology("must provide number of shares")

        ### If shares is not a positive integer, send apology
        try:
            int(request.form.get("shares"))
        except ValueError:
            return apology("shares must be a whole number greater than 0")

        if int(request.form.get("shares")) < 0:
            return apology("shares must be a whole number greater than 0")

        ### Lookup the symbol
        symbol = request.form.get("symbol")
        lookup_response = lookup(symbol)

        ### If lookup returns none, send apology
        if lookup_response == None:
            return apology("invalid stock symbol")
        else:
            price = lookup_response["price"]
            symbol = lookup_response["symbol"]
            shares = int(request.form.get("shares"))

        ### Calculate total cost of all the shares requested
        total_value = price * shares

        ### Query DB to ensure user owns the stock and ensure user is not trying to sell more shares than they own
        rows = db.execute("SELECT * FROM holdings WHERE userid = :userid AND symbol = :symbol",
                            userid=session["user_id"], symbol=symbol)
        if len(rows) < 1:
            return apology("you do not own any shares of that stock")

        elif rows[0]["shares"] < shares:
            return apology("you cannot sell more shares than you currently own")

        else:
            
            ### Update DB - subtract requested shares from current number of shares for that stock
            existing_shares = rows[0]["shares"]
            new_shares = existing_shares - shares

            ### Remove the record entirely from the holdings table if the number of shares goes down to 0 
            if new_shares == 0:
                db.execute("DELETE FROM holdings WHERE userid = :userid AND symbol = :symbol",
                            userid=session["user_id"], symbol=symbol)
            
            ### Update the holdings table to reflect the new number of shares
            else:
                db.execute("UPDATE holdings SET shares = :new_shares WHERE userid = :userid AND symbol = :symbol",
                            new_shares=new_shares, userid=session["user_id"], symbol=symbol)
        
            ### Add the value of the shares purchased to the user's cash, and update the DB with the new amount
            rows = db.execute("SELECT * FROM users WHERE id = :id",
                                id=session["user_id"]
                                )
            new_cash = rows[0]["cash"] + total_value

            db.execute("UPDATE users SET cash=:new_cash WHERE id = :id",
                        new_cash=new_cash, id=session["user_id"])

            ### Update the history table with the transaction
            action = "Sell"
            today = date.today()
            now = datetime.now()
            day = today.strftime("%d/%m/%Y") 
            time = now.strftime("%H:%M:%S")

            db.execute("INSERT INTO history (userid, action, symbol, price, shares, date, time) VALUES(:userid, :action, :symbol, :price, :shares, :day, :time)",
                        userid=session["user_id"], action=action, symbol=symbol, price=price, shares=shares, day=day, time=time)
            
            ### Redirect user to home page
            return redirect("/")


@app.route("/reset", methods=["GET", "POST"])
def reset():
    """Reset user password"""
    if request.method == "GET":

        ### Return register form
        return render_template("reset.html")

    else:

        ### Ensure password was submitted
        if not request.form.get("password") or not request.form.get("confirmation"):
            return apology("must provide new password", 403)

        ### Confirm passwords match
        if not (request.form.get("password") == request.form.get("confirmation")):
            return apology("passwords must match", 403)

        ### Check password complexity
        if complexity_check(request.form.get("password")):

            ### hash password
            hash = generate_password_hash(request.form.get("password"))

        else:
            return apology("password complexity requirements not met. Password must be at least 8 characters long and contain at least 1 number and 1 letter", 403)


        ### Update password hash in users table
        db.execute("UPDATE users SET hash = :hash WHERE id = :id",
                    hash=hash, id=session["user_id"])

        ### Redirect user to home page
        return redirect("/")


@app.route("/addcash", methods=["GET", "POST"])
def addcash():
    """Add additional cash to the account """
    if request.method == "GET":

        ### Return register form
        return render_template("addcash.html")

    else:

        ### Ensure amount was submitted and it is greater than 0
        if not request.form.get("amount"):
            return apology("must provide amount")

        try:
            float(request.form.get("amount"))
        except ValueError:
            return apology("amount must be a number")

        if float(request.form.get("amount")) < 0:
            return apology("amount must be greater than 0")

        ### Update cash amount in users table
        rows = db.execute("SELECT * FROM users WHERE id = :id",
                            id=session["user_id"])
        
        current_cash = float(rows[0]["cash"])
        new_cash = current_cash + float(request.form.get("amount"))

        rows = db.execute("UPDATE users SET cash = :new_cash WHERE id = :id",
                            id=session["user_id"], new_cash=new_cash)

        ### Redirect user to home page
        return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
