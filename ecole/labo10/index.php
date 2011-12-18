<?php
session_start();

if (!$_SESSION['user']) {
	header('Location: pass.php');
	exit();
}
?>
<html>
<head>
<title>Page protégée</title>
</head>
<body>
	<h1>Page protégée</h1>
	<p><strong>Connecté en tant que <?php echo $_SESSION['user']; ?></strong><p>
		
	<ul>
		<li><a href="gestion.php">Changer de mot de passe</a></li>
		<li><a href="pass.php">Déconnexion</a></li>
	<ul>
</body>
</html>
