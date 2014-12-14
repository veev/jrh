<!DOCTYPE html>
<html lang="en">
<head>
 	<meta charset=utf-8 />
 	<title>php info</title>
</head>

<body>


<?php
   $path = getcwd();
   echo "Your Absoluthe Path is: ";
   echo $path;
?>

<?php echo $_SERVER[".htpasswd"]; ?>

</body>
</html>
