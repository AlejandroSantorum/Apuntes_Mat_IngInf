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

package ssii2.visa.dao;
import ssii2.visa.*;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;


/**
 * @author jaime
 */
public class VisaDAO extends DBTester {

    private boolean debug = false;

    /**
     * TODO: Declarar un atributo booleano "prepared"
     * que indique si hay que usar prepared statements o no
     * Utilizar statements preparados o no
     */
    private boolean prepared = true;
    /***********************************************************/

    /* Para prepared statements, usamos cadenas constantes
     * Esto agiliza el trabajo del pool de statements */
    private static final String DELETE_PAGO_QRY =
        "delete from pago " +
        "where idComercio=?";
    private static final String SELECT_PAGOS_QRY =
        "select pago.* from pago, tarjeta " +
        "where idComercio=? and " +
        "pago.numeroTarjeta = tarjeta.numeroTarjeta";

    /**
     * TODO: Declarar consultas SQL estaticas
     * para uso con prepared statement
     * Hay que convertir las consultas de getQryXXX()
     */
    /*private static final String ...*/
    /**************************************************/
    private static final String SELECT_TARJETA_QRY =
                    "select * from tarjeta " +
                    "where numeroTarjeta=? " +
                    " and titular=? " +
                    " and validaDesde=? " +
                    " and validaHasta=? " +
                    " and codigoVerificacion=? ";

    private static final String INSERT_PAGOS_QRY =
                    "insert into pago(" +
                    "idTransaccion,importe,idComercio,numeroTarjeta)" +
                    " values (?,?,?,?)";

    private static final String SELECT_PAGO_TRANSACCION_QRY =
                    "select idAutorizacion, codRespuesta " +
                    " from pago " +
                    " where idTransaccion = ?" +
                    " and idComercio = ?";
    /**************************************************/

    
    /**
     * Constructor de la clase     
     */
    public VisaDAO() {
        return;
    }


    /**
     *  getQryCompruebaTarjeta
     */
    String getQryCompruebaTarjeta(TarjetaBean tarjeta) {
        String qry = "select * from tarjeta "
                    + "where numeroTarjeta='" + tarjeta.getNumero()
                    + "' and titular='" + tarjeta.getTitular()
                    + "' and validaDesde='" + tarjeta.getFechaEmision()
                    + "' and validaHasta='" + tarjeta.getFechaCaducidad()
                    + "' and codigoVerificacion='" + tarjeta.getCodigoVerificacion() + "'";
        return qry;
    }
    
    /**
     *  getQryInsertPago
     */
    String getQryInsertPago(PagoBean pago) {
        String qry = "insert into pago("
                    + "idTransaccion,"
                    + "importe,idComercio,"
                    + "numeroTarjeta)"
                    + " values ("
                    + "'" + pago.getIdTransaccion() + "',"
                    + pago.getImporte() + ","
                    + "'" + pago.getIdComercio() + "',"
                    + "'" + pago.getTarjeta().getNumero() + "'"
                    + ")";
        return qry;
    }

    /**
     *  getQryBuscaPagoTransaccion()
     */
    String getQryBuscaPagoTransaccion(PagoBean pago) {
        String qry = "select idAutorizacion, codRespuesta "
                        + " from pago "
                        + " where idTransaccion = '" + pago.getIdTransaccion()
                        + "'   and idComercio = '" + pago.getIdComercio() + "'";
        return qry;
    }


    /**
     *
     * Comprobacion de la tarjeta
     * @param tarjeta Objeto con toda la informacion de la tarjeta
     * @return true si la comprobacion contra las tarjetas contenidas en
     *         en la tabla TARJETA fue satisfactoria, false en caso contrario     */
    public boolean compruebaTarjeta(TarjetaBean tarjeta) {
        Connection con = null;
        Statement stmt = null;
        ResultSet rs = null;
        boolean ret = false;
        String qry = null;

        // TODO: Utilizar en funcion de isPrepared()
        PreparedStatement pstmt = null;

        try {

            // Crear una conexion u obtenerla del pool
            con = getConnection();

            // Se busca la ocurrencia de la tarjeta en la tabla

            /* TODO Usar prepared statement si
               isPrepared() == true */
            /**************************************************/
            if (isPrepared() == true) {
               String select  = SELECT_TARJETA_QRY;
               errorLog(select);
               pstmt = con.prepareStatement(select);
               pstmt.setString(1, tarjeta.getNumero());
               pstmt.setString(2, tarjeta.getTitular());
               pstmt.setString(3, tarjeta.getFechaEmision());
               pstmt.setString(4, tarjeta.getFechaCaducidad());
               pstmt.setString(5, tarjeta.getCodigoVerificacion());
               rs = pstmt.executeQuery();               

            } else {
            /**************************************************/
            stmt = con.createStatement();
            qry = getQryCompruebaTarjeta(tarjeta);
            errorLog(qry);
            rs = stmt.executeQuery(qry);

            } /**********************/
            
            /* Si hay siguiente registro, la tarjeta valido OK */
            ret = rs.next();

        } catch (Exception ee) {
            errorLog(ee.toString());
            ret = false;
        } finally {
            try {
                if (rs != null) {
                    rs.close(); rs = null;
                }
                if (stmt != null) {
                    stmt.close(); stmt = null;
                }
                if (pstmt != null) {
                    pstmt.close(); pstmt = null;
                }
                if (con != null) {
                    closeConnection(con); con = null;
                }
            } catch (SQLException e) {
            }
        }

        return ret;

    }

    /**
     * Realiza el pago 
     * @param pago
     * @return
     */
    public synchronized boolean realizaPago(PagoBean pago) {
        Connection con = null;
        Statement stmt = null;
        ResultSet rs = null;
        boolean ret = false;
        String codRespuesta = "999"; // En principio, denegado

        // TODO: Utilizar en funcion de isPrepared()
        PreparedStatement pstmt = null;

        // Calcular pago.
        // Comprobar id.transaccion - si no existe,
        // es que la tarjeta no fue comprobada
        if (pago.getIdTransaccion() == null) {
            return false;
        }

        // Registrar el pago en la base de datos
        try {

            // Obtener conexion
            con = getConnection();

            // Insertar en la base de datos el pago

            /* TODO Usar prepared statement si
               isPrepared() == true */
            /**************************************************/
            if (isPrepared() == true) {
               String insert  = INSERT_PAGOS_QRY;
               errorLog(insert);
               pstmt = con.prepareStatement(insert);
               pstmt.setString(1, pago.getIdTransaccion());
               pstmt.setDouble(2, pago.getImporte());
               pstmt.setString(3, pago.getIdComercio());
               pstmt.setString(4, pago.getTarjeta().getNumero());
               ret = false;
               if (!pstmt.execute()
                       && pstmt.getUpdateCount() == 1) {
                 ret = true;
               }

            } else {            
            /**************************************************/
            stmt = con.createStatement();
            String insert = getQryInsertPago(pago);
            errorLog(insert);
            ret = false;
            if (!stmt.execute(insert)
                    && stmt.getUpdateCount() == 1) {
                ret = true;
			}
            }/****************/

            // Obtener id.autorizacion
            if (ret) {                

                /* TODO Permitir usar prepared statement si
                 * isPrepared() = true */
                /**************************************************/
                if (isPrepared() == true) {
                    String select = SELECT_PAGO_TRANSACCION_QRY;
                    errorLog(select);
                    pstmt = con.prepareStatement(select);
                    pstmt.setString(1, pago.getIdTransaccion());
                    pstmt.setString(2, pago.getIdComercio());
                    rs = pstmt.executeQuery();
                } else {
                /**************************************************/

                    String select = getQryBuscaPagoTransaccion(pago);
                    errorLog(select);
                    rs = stmt.executeQuery(select);
                    
                }/*************************************/
                if (rs.next()) {
                    pago.setIdAutorizacion(String.valueOf(rs.getInt("idAutorizacion")));
                    pago.setCodRespuesta(rs.getString("codRespuesta"));
                } else {
                    ret = false;
                }

            }

        } catch (Exception e) {
            errorLog(e.toString());
            ret = false;
        } finally {
            try {
                if (rs != null) {
                    rs.close(); rs = null;
                }
                if (stmt != null) {
                    stmt.close(); stmt = null;
                }
                if (pstmt != null) {
                    pstmt.close(); pstmt = null;
                }
                if (con != null) {
                    closeConnection(con); con = null;
                }
            } catch (SQLException e) {
            }
        }

        return ret;
    }


    /**
     * Buscar los pagos asociados a un comercio
     * @param idComercio
     * @return
     */
    public PagoBean[] getPagos(String idComercio) {

        PreparedStatement pstmt = null;
        Connection pcon = null;
        ResultSet rs = null;
        PagoBean[] ret = null;
        ArrayList<PagoBean> pagos = null;
        String qry = null;

        try {

            // Crear una conexion u obtenerla del pool
            pcon = getConnection();
            qry = SELECT_PAGOS_QRY;
            errorLog(qry + "[idComercio=" + idComercio + "]");

            // La preparacion del statement
            // es automaticamente tomada de un pool en caso
            // de que ya haya sido preparada con anterioridad
            pstmt = pcon.prepareStatement(qry);

            pstmt.setString(1, idComercio);
            rs = pstmt.executeQuery();

            pagos = new ArrayList<PagoBean>();

            while (rs.next()) {
                TarjetaBean t = new TarjetaBean();
                PagoBean p = new PagoBean();
                p.setIdTransaccion(rs.getString("idTransaccion"));
                p.setIdComercio(rs.getString("idComercio"));
                p.setImporte(rs.getFloat("importe"));
                t.setNumero(rs.getString("numeroTarjeta"));
                p.setTarjeta(t);
                p.setCodRespuesta(rs.getString("codRespuesta"));
                p.setIdAutorizacion(String.valueOf(rs.getInt("idAutorizacion")));

                pagos.add(p);
            }

            ret = new PagoBean[pagos.size()];
            ret = pagos.toArray(ret);

            // Cerramos / devolvemos la conexion al pool
            pcon.close();

        } catch (Exception e) {
            errorLog(e.toString());

        } finally {
            try {
                if (rs != null) {
                    rs.close(); rs = null;
                }
                if (pstmt != null) {
                    pstmt.close(); pstmt = null;
                }
                if (pcon != null) {
                    closeConnection(pcon); pcon = null;
                }
            } catch (SQLException e) {
            }
        }

        return ret;
    }

    // Borrar los pagos asociados a un comercio
    /**
     *
     * @param idComercio
     * @return numero de registros afectados
     */
    public int delPagos(String idComercio) {

        PreparedStatement pstmt = null;
        Connection pcon = null;
        ResultSet rs = null;
        int ret = 0;
        String qry = null;

        try {

            // Crear una conexion u obtenerla del pool
            pcon = getConnection();
            qry = DELETE_PAGO_QRY;
            errorLog(qry + "[idComercio=" + idComercio + "]");

            // La preparacion del statement
            // es automaticamente tomada de un pool en caso
            // de que ya haya sido preparada con anterioridad
            pstmt = pcon.prepareStatement(qry);
            pstmt.setString(1, idComercio);
            ret = pstmt.executeUpdate();

            // Cerramos / devolvemos la conexion al pool
            pcon.close();

        } catch (Exception e) {
            errorLog(e.toString());

        } finally {
            try {
                if (rs != null) {
                    rs.close(); rs = null;
                }
                if (pstmt != null) {
                    pstmt.close(); pstmt = null;
                }
                if (pcon != null) {
                    closeConnection(pcon); pcon = null;
                }
            } catch (SQLException e) {
            }
        }

        return ret;
    }

    /**
     * TODO: Metodos isPrepared() y setPrepared()
     */
    /********************************************************/
    public boolean isPrepared() {
        return prepared;
    }

    public void setPrepared(boolean prepared) {
        this.prepared = prepared;
    }
    /********************************************************/

    /**
     * @return the debug
     */
    public boolean isDebug() {
        return debug;
    }

    /**
     * @param debug the debug to set
     */
    public void setDebug(boolean debug) {
        this.debug = debug;
    }

    /**
     * @param debug the debug to set
     */
    public void setDebug(String debug) {
        this.debug = (debug.equals("true"));
    }


    /**
     * Imprime traza de depuracion
     */
    public void errorLog(String error) {
        if (isDebug())
            System.err.println("[directConnection=" + this.isDirectConnection() +"] " +
                               error);
    }

}
