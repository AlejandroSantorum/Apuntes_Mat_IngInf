/**
 * Pr&aacute;ctricas de Sistemas Inform&aacute;ticos II
 * 
 * Clase que representa un error en el campo c&oacute;digo de verificaci&oacute;n
 */

package ssii2.visa.error;

import ssii2.visa.TarjetaBean;

/**
 *
 * @author phaya
 */
public class ErrorVisaCVV extends ErrorVisa {

    public ErrorVisaCVV(TarjetaBean t, String causa) {
        super(t, causa);
    }

}
