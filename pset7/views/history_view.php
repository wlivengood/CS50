<table class="table table-striped">

    <thead>
        <tr>
            <th>Transaction</th>
            <th>Date/time</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
    </thead>

    <tbody>
    <?php foreach ($positions as $position): ?>
    <tr>
        <td><?= $position["transaction"] ?></td>
        <td><?= date('F d, Y h:mA', strtotime($position["time_stamp"])) ?></td>
        <td><?= $position["symbol"] ?></td>
        <td><?= $position["shares"] ?></td>
        <td>$<?= number_format($position["price"], 2) ?></td>
    </tr>
    <?php endforeach ?>
    </tbody>
</table>
