/**
 *
 */
package padsof;

/**
 * @author Alejandro Santorum, David Cabornero
 * This enumerations shows the status of an offer: it can be
 * free (not rented), rented, booked, out of range of dates, waiting
 * to be allowed by the manager or denied by the manager.
 */
public enum Status {
	FREE,
	RENTED,
	BOOKED,
	WAITING,
	OUT,
	DENIED;
}
