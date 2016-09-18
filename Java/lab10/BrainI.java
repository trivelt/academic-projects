
public interface BrainI {
/**
 * Przekazuje referencje do obiektu typu GameI
 * @param gi referencja do obiektu typu GameI
 */
	public void setGameI( GameI gi );
	
/**
 * Rozpoczyna gre. Od tej chwili sterowanie przejmuje na siebie kod klasy zgodnej z BrainI
 */
	public void start();
}
