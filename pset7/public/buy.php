<?php

    // configuration
    require("../includes/config.php"); 
    
    // if method is GET, render form
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
       render("buy_form.php", ["title" => "Buy"]); 
    }
    
    // else if method is POST
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
    
    // error checking
        if (empty($_POST["symbol"]))
        {
            apologize("You must select a stock to buy");
        }
        
        $stock = lookup($_POST["symbol"]);
        
        if ($stock == false)
        {
            apologize("Symbol was not recognized");
        }
        
        if (empty($_POST["shares"]))
        {
            apologize("You must specify a number of shares");
        }
        
        // check for positive integer
        if(preg_match("/^\d+$/", $_POST["shares"]) == false)
        {
            apologize("Invalid number of shares");
        }
        
        // convert symbol to uppercase
        $symbol = strtoupper($_POST["symbol"]);
        
        $price = $stock["price"];
        
        $shares = $_POST["shares"];
        
        // calculate total cost of shares
        $total = $price * $shares;
        
        // check if cost is greater than available cash
        if ($total > $_SESSION["cash"])
        {
            apologize("You can't afford that!");
        }
        
        else
        {
            // insert stock into portfolio
            $query = CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $symbol, $shares);
            // register in history
            $query = CS50::query("INSERT INTO history (user_id, transaction, time_stamp, symbol, shares, price) VALUES(?, 'BUY', now(), ?, ?, ?)", $_SESSION["id"], $symbol, $shares, $price);
            // update cash amount in users table
            $query = CS50::query("UPDATE users SET cash = ? - ? WHERE id = ?", $_SESSION["cash"], $total, $_SESSION["id"]);
            // set cash session super global to new amount
            $rows = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
            $_SESSION["cash"] = $rows[0]["cash"];
            // return to index
            redirect("/");
        }
    }
?>