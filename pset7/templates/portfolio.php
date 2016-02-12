<div>
    <table class="table table-striped">
        <thead>
            <tr>
                <th>Symbol</th>
                <th>Name</th>
                <th>Shares</th>
                <th>Price</th>
                <th>TOTAL</th>
            </tr>
        </thead>
        <tbody>
            <?php if (!is_null($positions[0]["name"])) foreach ($positions as $position): ?>

                <tr>
                    <td><?= $position["symbol"] ?></td>
                    <td><?= $position["name"] ?></td>
                    <td><?= $position["shares"] ?></td>
                    <td><?= $position["price"] ?></td>
                    <td><?= $position["total"] ?></td>
                </tr>

            <?php endforeach ?>
        
                <tr>
                    <td colspan="4">CASH</td>
                    <td><?= $cash ?></td>
                </tr>
        </tbody>
    </table>
</div>
<div>
    <a href="logout.php">Log Out</a>
</div>
