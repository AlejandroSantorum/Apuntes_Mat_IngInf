<?php
print "Ejemplo de transacciones en PHP-PDO.<p>";
try{
	$db = new PDO('sqlite:sqlite.db');
	$sql = "SELECT * FROM actor";
	foreach ($db->query($sql) as $row){
		print $row['actor_id'] .' - '. $row['name'] . '<br/>';
	}
}
catch (Exception $e){
	print "Un error<p>";
	echo $e->getMessage();
	print "<p>";
}

// Continuar la ejecución
echo 'Fin del script';

?>
