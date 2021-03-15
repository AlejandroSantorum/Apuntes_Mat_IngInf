/**
 * Pr&aacute;ctricas de Sistemas Inform&aacute;ticos II
 * 
 * Clase que representa un error en el campo n&uacute;mero de la tarjeta
 */

package ssii2.visa.error;

import ssii2.visa.TarjetaBean;

/**
 *
 * @author phaya
 */
public class ErrorVisaNumero extends ErrorVisa {

    public ErrorVisaNumero(TarjetaBean t, String causa) {
        super(t, causa);
    }
    
}
