<html>
<head>
<title>Explorateur</title>
</head>
<body>
<h1>Explorateur</h1>
<?php
function rec_dir($file = '.')
{
	if (is_dir($file)) {
		echo '<strong>', $file, '</strong>';
		echo '<ul>';
		$dir = opendir($file);
		while ($f = readdir($dir)) {
			if ($f[0] != '.') // Passe les fichiers cachés et les liens système
				echo '<li>', rec_dir($file . '/' . $f), '</li>';
		}
		closedir($dir);
		echo '</ul>';
	} else
		echo '<a href="'.$file.'">', $file, '</a>';
}

rec_dir();
?>
</body>
</html>
