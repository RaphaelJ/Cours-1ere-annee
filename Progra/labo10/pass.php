<?php
session_start();

$message = 'Bievenue';

if (isset($_SESSION['user'])) {
	unset($_SESSION['user']); // Déconnexion
	$message = 'Déconnexion réussie';
}

if (isset($_SESSION['nb_essais'])) {
	$nb_essais = $_SESSION['nb_essais'];
} else
	$nb_essais = 0;

if (isset($_POST['user'], $_POST['pass'])) {
	$mysql = new mysqli('10.59.26.210', 'user261', 'D4H2cu',
			'user261');
	
	$result = $mysql->query('SELECT 1
		FROM php_user
		WHERE login = \''. $_POST['user'] .'\'
		  AND mdp = \''. sha1($_POST['pass']) .'\'');
	
	if ($result->num_rows) {
		$_SESSION['user'] = $_POST['user'];
		header('Location: index.php');
		unset($_SESSION['nb_essais']);
		exit();
	} else {
		$_SESSION['nb_essais'] = ++$nb_essais;
		$message = 'Mauvais identifiants';
	}
}		
?>
<html>
<head>
<title>Connexion</title>
</head>
<body>
	<h1>Connexion</h1>
	<?php
	echo '<p><strong>', $message, '</strong></p>';

	if ($nb_essais <= 3) {
		?>
		<form action="#" method="post">
			<label for="user">Utilisateur: </label>
				<input type="text" name="user"/>
			<br />
			<label for="pass">Mot de passe: </label>
				<input type="password" name="pass"/>
			<br />
				
			<input type="submit"/>
		</form>
		<?php
	} else {
		?>
		<p><strong>Vous ne pouvez pas essayer de vous connecter plus de 3 fois</strong></p>
		<?php
	}
	?>
</body>
</html>
