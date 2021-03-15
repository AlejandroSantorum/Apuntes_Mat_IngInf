/**
 * Pr&aacute;ctricas de Sistemas Inform&aacute;ticos II
 * 
 * Implementacion de la interfaz de VISA utilizando como backend
 * una base de datos.
 * Implementa dos modos de acceso (proporcionados por la clase DBTester):
 * - Conexion directa: mediante instanciacion del driver y creacion de conexiones
 * - Conexion a traves de datasource: obtiene nuevas conexiones de un pool identificado
 *   a traves del nombre del datasource (DSN)
 *
 */

package ssii2.visa;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import javax.ejb.Local;

@Local
public interface VisaDAOLocal {
    public boolean compruebaTarjeta(TarjetaBean tarjeta);
    public PagoBean realizaPago(PagoBean pago);	
    public PagoBean[] getPagos(String idComercio);
    public int delPagos(String idComercio);
    public boolean isDebug();
    public boolean isPrepared();
    public void setPrepared(boolean prepared); 
    public void setDebug(boolean debug);
    public int getDirectConnectionCount();
    public int getDSNConnectionCount();
    public boolean isDirectConnection();    
    public void setDirectConnection(boolean directConnection);
}    

