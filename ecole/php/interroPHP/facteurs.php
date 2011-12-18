<?php
if (isset($_GET['nombre']) && !empty($_GET['nombre'])) {
	$nombre = intval($_GET['nombre']);
} else {
	header('Location: inpnum.php');
	die();
}

/* Retourne le nombre premier suivant */
function suivantPremier($nb = 1)
{
	do {
		$div = $nb++;
		while ($div >= ($nb / 2) && ($nb % $div) != 0)
			$div--;
	} while ($div >= ($nb / 2));

	return $nb;
}

?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8"/> 
        <title>Factorisation d'un nombre premier</title>
        <style type="text/css">
                h1, h2 {
                        text-shadow: grey 0px 0px 4px /* CSS 3 */
                }
		.erreur {
			text-align: center;
			margin: auto;
			padding: 10px;
			border-color: red;
			color: white;
			font-weight: bold;
			background-color: #AA3333;
		}
        </style>
        <link rel="icon" type="image/jpg" href="pi.jpg" />
</head>
<body>
<h1>Factorisation d'un nombre premier</h1>
<p>
	<a href="inpnum.php">Retour</a>
</p>
<hr />

<h2><?php echo $nombre; ?></h2>

<?php
	if ($nombre <= 1)
		echo '<div class="erreur">Le nombre doit être plus grand que 1</div>';
	else {
		$div = 2;
		while ($nombre > 1) {
			if (($nombre % $div) != 0)
				$div = suivantPremier($div);
			else {
				if ($nombre == $div)
					echo '<strong>'.$nombre.' / '.$div.'</strong>';
				else 
					echo $nombre .' / '. $div .'<br/>';

				$nombre /= $div;
				
			}
		}
	}
?>

</body>
</html>
