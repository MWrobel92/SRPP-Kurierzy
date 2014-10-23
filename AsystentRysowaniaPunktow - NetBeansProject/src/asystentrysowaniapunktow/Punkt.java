/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package asystentrysowaniapunktow;

/**
 *
 * @author Michal
 */
public class Punkt {
    
    int x;
    int y;
    
    Punkt (int id, int x, int y) {
        this.x = x;
        this.y = y;
    }

    Punkt(String x, String y) {
        this.x = Integer.parseInt(x);
        this.y = Integer.parseInt(y);
    }
    
}
