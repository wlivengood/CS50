<?php

    // configuration
    require("../includes/config.php"); 
    
    // query portfolios for symbol and shares
    $rows = CS50::query("SELECT symbol, shares FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
    
    // create array to hold key-value arrays
    $positions = [];
    foreach ($rows as $row)
    {
        // look up stock and include name and price in array
        $stock = lookup($row["symbol"]);
            if ($stock !== false)
            {
            $positions[] = [
            "name" => $stock["name"],
            "price" => $stock["price"],
            "shares" => $row["shares"],
            "symbol" => $row["symbol"]
            ];
            }
    }
    
    // pass array to portfolio.php via render
    render("portfolio.php", ["positions" => $positions, "title" => "Portfolio"]);
?>
