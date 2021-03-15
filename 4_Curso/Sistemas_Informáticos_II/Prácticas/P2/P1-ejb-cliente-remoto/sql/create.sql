-- Tabla con tarjetas validas
CREATE TABLE tarjeta
(
numeroTarjeta      char(19) not null,
titular            varchar(128) not null,
validaDesde        char(5) not null,
validaHasta        char(5) not null,
codigoVerificacion char(3) not null,
PRIMARY KEY (numeroTarjeta)
);

INSERT INTO tarjeta(numeroTarjeta,titular,validaDesde,validaHasta,codigoVerificacion)
VALUES ('1111 2222 3333 4444','Jose Garcia','11/09','11/20','123');

-- Tabla con pagos autorizados
-- Siempre vienen precedidos por una transaccion existente
CREATE TABLE pago
(
-- idAutorizacion se autogenera con cada inserción
idAutorizacion serial   not null,
idTransaccion  char(16) not null,
codRespuesta   char(3)  not null default '000',
importe        float    not null,
idComercio     char(16) not null,
numeroTarjeta  char(19) not null references tarjeta,
fecha          timestamp not null default current_timestamp,
CONSTRAINT     Pago_UC  unique(idTransaccion, idComercio),
PRIMARY KEY (idAutorizacion)
);

-- INSERT INTO pago(idAutorizacion,idTransaccion, codRespuesta, importe, idComercio, numeroTarjeta)
-- VALUES (NEXTVAL(pago_idAutorizacion_seq), 1,'000', 123.00, '0000000000000000', '1111 2222 3333 4444');

