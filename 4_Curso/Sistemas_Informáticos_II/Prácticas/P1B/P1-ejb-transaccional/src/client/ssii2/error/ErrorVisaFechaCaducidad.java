/**
 * Pr&aacute;ctricas de Sistemas Inform&aacute;ticos II
 * 
 * Clase que representa un error en el campo fecha de caducidad
 */

package ssii2.visa.error;

import ssii2.visa.TarjetaBean;

/**
 *
 * @author phaya
 */
public class ErrorVisaFechaCaducidad extends ErrorVisa {

    public ErrorVisaFechaCaducidad(TarjetaBean t, String causa) {
        super(t, causa);
    }


}
