// Solucion al ejercicio de mongoDB propuesto en clase de teoria
// (C) JAMI. Sistemas Informaticos 1. EPS-UAM
// Este script se puede ejecutar directamente (shell) de la forma "mongo nombre_fichero.js"

db = db.getSiblingDB("mi_base_de_datos")

// Creacion de documentos (1 por universidad, junto con sus centros propios correspondientes)
// Solo se muestra el caso completo de la UAM. Completar para el resto de universidades siguiendo el mismo patron

db.universidades.drop()
db.createCollection("universidades")

db.universidades.insertOne({
    nombre: "UAM",
    direccion_postal: "Ciudad Universitaria de Cantoblanco. 28049 Madrid",
    email: "informacion.general@uam.es",
    pagina_web: "http://www.uam.es",
    telefono: "914975000",
    centros: [
        {nombre:"Escuela Politecnica Superior", estudiantes:1198},
        {nombre:"Facultad de Derecho", estudiantes:3193},
        {nombre:"Facultad de Filosofia y Letras", estudiantes:3783},
        {nombre:"Facultad de Ciencias", estudiantes:4285},
        {nombre:"Facultad de Formacion de Profesorado y Educacion", estudiantes:2433},
        {nombre:"Facultad de Medicina", estudiantes:2071},
        {nombre:"Facultad de Ciencias Economicas y Empresariales", estudiantes:2886},
        {nombre:"Facultad de Psicologia", estudiantes:1505}
    ]
})

db.universidades.insertOne({
    nombre: "UCM",
    direccion_postal: "Avenida Seneca 2. 28040 Madrid",
    email: "infocom@ucm.es",
    pagina_web: "http://www.ucm.es",
    telefono: "914520400",
    centros: [
        {nombre:"Facultad de Derecho", estudiantes:5133},
        {nombre:"Facultad de Informatica", estudiantes:1736},
        {nombre:"Facultad de Matematicas", estudiantes:1240},
        {nombre:"Facultad de Farmacia", estudiantes:2350}
    ]
})

db.universidades.insertOne({
    nombre: "UPM",
    direccion_postal: "Paseo Juan XXIII 11. 28040 Madrid",
    email: "informacion@upm.es",
    pagina_web: "http://www.upm.es",
    telefono: "913366000",
    centros: [
        {nombre:"E.T.S. de Ingenieros Informaticos", estudiantes:800},
        {nombre:"E.T.S. de Ingenieros de Telecomunicacion", estudiantes:700}
    ]
})


// Consulta: Centros de la UAM

print("Centros de la UAM:")

cursor1 = db.universidades.find({nombre:"UAM"},{
    _id:0,
    nombre:1,
    "centros.nombre":1
})

while (cursor1.hasNext() ) {
   printjson(cursor1.next() );
}


// Consulta: Total de estudiantes por universidad

print("Total de Estudiantes por Universidad:")

cursor2 = db.universidades.aggregate([{
    $project: {
        _id:0,
        nombre:1,
        "Total de Estudiantes": {$sum: "$centros.estudiantes"}
    }
}])

while (cursor2.hasNext() ) {
   printjson(cursor2.next() );
}


// Consulta: Universidades con facultades de Derecho

print("Universidades con Facultades de Derecho:")

cursor3 = db.universidades.aggregate([
    {$match:{"centros.nombre":{$regex:"derecho", $options: "$i"}}},
    {$group: {
        _id:"$nombre"

     }}
])

while (cursor3.hasNext() ) {
   printjson(cursor3.next() );
}
