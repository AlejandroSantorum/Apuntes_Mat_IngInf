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
	$db->beginTransaction();
	printTableActor($db);
	$sql = "DELETE FROM actor WHERE actor_id=3";
	$result = $db->exec($sql);
	if ($result === FALSE){
		print "Error detectado en DELETE 1<p>";
		$db->rollBack();
		die();
	} else {
		print "Filas afectadas por exec:" . $result . '<p>';
	}
	printTableActor($db);
	$sql = "DELETE FROM actor WHERE actor_id=1";
	$result = $db->exec($sql);
	if ($result === FALSE){
		print "Error detectado en DELETE 2<p>";
		$db->rollBack();
		die();

	} else {
		print "Filas afectadas por exec:" . $result . '<p>';
	}
	printTableActor($db);
	$db->commit();

}
catch (Exception $e){
	print "Un error<p>";
	echo $e->getMessage() . "<p>";
}
// Continuar la ejecución
echo 'Fin del script';
?>


