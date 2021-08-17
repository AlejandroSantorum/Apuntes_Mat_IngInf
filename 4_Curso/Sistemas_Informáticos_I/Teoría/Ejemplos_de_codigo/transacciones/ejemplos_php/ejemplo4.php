<?php
function printTableActor($dbRef){
	$sql = "SELECT * FROM actor";
	foreach ($dbRef->query($sql) as $row){
		print $row['actor_id'] .' - '. $row['name'] . '<br/>';
	}
	print '<p>';
}
print "Ejemplo de transacciones en PHP-PDO.<p>";
try{
	$db = new PDO('sqlite:sqlite.db');
	printTableActor($db);
	$sql = "DELETE FROM actor WHERE actor_id=3";
	$db->exec($sql);
	printTableActor($db);
}
catch (Exception $e){
	print "Un error<p>";
	echo $e->getMessage() . "<p>";
}
// Continuar la ejecución
echo 'Fin del script';
?>

