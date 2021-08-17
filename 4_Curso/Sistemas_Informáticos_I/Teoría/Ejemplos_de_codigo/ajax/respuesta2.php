
<?php
//print_r($_REQUEST);
if ($_REQUEST["comida"]=="cangreburger")
	echo "¡Por supuesto señor! ¿Cuántas quiere?";
else
	echo "Lo sentimos, no tenemos " . $_REQUEST["comida"] . " en este local. Pruebe en El Cubo de Cebo";
?>
