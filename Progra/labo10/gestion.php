<?php
session_start();

if (!$_SESSION['user']) {
	header('Location: pass.php');
	exit();
}

if ($_POST) {
	if ($_POST['pass1'] and $_POST['pass1'] == $_POST['pass2']) {
		$mysql = new mysqli('10.59.26.210', 'user261', 'D4H2cu',
        	                'user261');
	        $result = $mysql->query('UPDATE php_user
			SET mdp = \''. sha1($_POST['pass1']) .'\'
                	WHERE login = \''. $_SESSION['user'] .'\'');

		$message = 'Mot de passe modifié avec succès';
	} else 
		$message = 'Les mots de passes ne sont pas identiques';
} else
	$message = 'Entrez votre mot de passe';
?>
<html>
<head>
<title>Modifier le mot de passe</title>
</head>
<body>
	<h1>Modifier le mot de passe</h1>
		
	<p><strong><?php echo $message; ?></strong>

	<form method="post" action="#">
		<label for="pass1">Mot de passe: </label>
			<input name="pass1" type="password" />
		<br />

		<label for="pass2">Vérification: </label>
			<input name="pass2" type="password" />
		<br />

		<input type="submit" value="Modifier" />
	</form>

	<a href="index.php">Retour à l'index</a>
</body>
</html>
