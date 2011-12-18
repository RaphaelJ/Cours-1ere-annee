<?php
if (!isset($_POST['ch1'], $_POST['ch2'], $_POST['ch3'],
	$_POST['ch4'], $_POST['ch5'])) {
	header('Location: inptxt.php');
	die();
}
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8"/> 
        <title>Concaténation et hash</title>
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
<h1>Concaténation et hash</h1>
<p>
	<a href="inptxt.php">Retour</a>
</p>
<hr />

<?php
	if (strlen($_POST["ch1"]) < 1 || strlen($_POST["ch2"]) < 2
	    || strlen($_POST["ch3"]) < 3 || strlen($_POST["ch4"]) < 4
	    || strlen($_POST["ch5"]) < 5)
		echo '<div class="erreur">Les chaines ne sont pas assez longues</div>';
	else {
		$chaine = $_POST["ch1"]{0}.$_POST["ch2"]{1}.$_POST["ch3"]{2}
			.$_POST["ch4"]{3}.$_POST["ch5"]{4};

		echo 'md5("'.$chaine.'") = '.md5($chaine);

	}
?>

</body>
</html>
