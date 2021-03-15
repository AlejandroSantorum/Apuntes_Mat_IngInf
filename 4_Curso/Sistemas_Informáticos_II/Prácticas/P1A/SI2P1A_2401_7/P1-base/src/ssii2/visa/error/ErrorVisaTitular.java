/**
 * Pr&aacute;ctricas de Sistemas Inform&aacute;ticos II
 * 
 * Clase que representa un error en el campo titular de la tarjeta
 */

package ssii2.visa.error;

import ssii2.visa.TarjetaBean;

/**
 *
 * @author phaya
 */
public class ErrorVisaTitular extends ErrorVisa  {

    public ErrorVisaTitular(TarjetaBean t, String causa) {
        super(t, causa);
    }
}
