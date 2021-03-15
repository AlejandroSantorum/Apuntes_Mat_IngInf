/**
 * Pr&aacute;ctricas de Sistemas Inform&aacute;ticos II
 * 
 * Clase que representa un error en el campo fecha de emisi&oacute;n
 */

package ssii2.visa.error;

import ssii2.visa.TarjetaBean;

/**
 *
 * @author phaya
 */
public class ErrorVisaFechaEmision extends ErrorVisa {

    public ErrorVisaFechaEmision(TarjetaBean t, String causa) {
        super(t, causa);
    }

}
