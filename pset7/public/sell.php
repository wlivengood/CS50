<?php

    // configuration
    require("../includes/config.php"); 
    
    // if method is get, render sell_form
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
       // query portfolios for available symbols, pass to sell_form via render()
       $symbols = CS50::query("SELECT symbol FROM portfolios WHERE user_id = ?", $_SESSION["id"]); 
       render("sell_form.php", ["title" => "Sell", "symbols" => $symbols]); 
    }
    
    // else if method is POST
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // check if symbol has been provided
        if (empty($_POST["symbol"]))
        {
            apologize("You must select a stock to sell");
        }
        
        $stock = lookup($_POST["symbol"]);
        
        // check is symbol was recognized
        if ($stock == false)
        {
            apologize("Symbol was not recognized");
        }
        
        
        $price = $stock["price"];
        // pull number of shares of symbol for user from portfolios
        $rows = CS50::query("SELECT shares FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        $num_shares = $rows[0]["shares"];
        // calculate total value
        $total = $price * $num_shares;
        // add cash to users table
        $query = CS50::query("UPDATE users SET cash = ? + ? WHERE id = ?", $_SESSION["cash"], $total, $_SESSION["id"]);
        // remove stock from portfolios
        $query = CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        // register transaction in history
        $query = CS50::query("INSERT INTO history (user_id, transaction, time_stamp, symbol, shares, price) VALUES(?, 'SELL', now(), ?, ?, ?)", $_SESSION["id"], $_POST["symbol"], $num_shares, $price);
        // update cash session superglobal
        $rows = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        $_SESSION["cash"] = $rows[0]["cash"];
        // redirect to index
        redirect("/");
    }
?>