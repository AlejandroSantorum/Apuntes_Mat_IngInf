import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class TxSQLite {

	public static final String URL_BD = "jdbc:sqlite:sqlite.db";

	public static void main(String[] args) {
		Connection conexion = null;
		int actor_id = 0;

		try {
			// Adquisición del driver y conexión con la base de datos
			Class.forName("org.sqlite.JDBC");
			conexion = DriverManager.getConnection(URL_BD);
			conexion.setAutoCommit(false);

			// Transacción para insertar un nuevo actor y sus películas
			PreparedStatement qry1 = conexion.prepareStatement(
					"INSERT INTO Actor (name) VALUES (?)", Statement.RETURN_GENERATED_KEYS);
			PreparedStatement qry2 = conexion.prepareStatement(
					"INSERT INTO Film_Actor (actor_id, film_id) " +
					"SELECT ?, name FROM Film WHERE name = ?");

			qry1.setString(1, "Sean Connery");
			if(qry1.executeUpdate() == 1) {
				ResultSet rs = qry1.getGeneratedKeys();
				rs.next();
				actor_id = rs.getInt(1);

				qry2.setInt(1, actor_id);
				qry2.setString(2, "Indiana Jones and the Last Crusade");
				qry2.execute();

				conexion.commit();
			}
			else {
				conexion.rollback();
			}

			conexion.close();
		}
		catch(Exception err) {
			err.printStackTrace();
			if(conexion != null)
			{
				try {
					conexion.rollback();
					conexion.close();
				}
				catch(SQLException err2) {}
			}
		}
	}
}
