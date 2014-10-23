/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package asystentrysowaniapunktow;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import javax.imageio.ImageIO;
import javax.swing.JPanel;

/**
 *
 * @author Michal
 */
class PanelRysowania extends JPanel {
    
    private int wysokosc;
    private int szerokosc;
    private int margines;
    
    private int xmin;
    private int xmax;
    private int ymin;
    private int ymax;
    
    private double skala;
    
    private ArrayList<Punkt> miasta;
    private ArrayList<ArrayList<Integer>> sciezki;
    
    private int przeliczX (int xr) {
        double wynik = (xr - xmin)*skala + margines;
        return (int)wynik;
    }
    
    private int przeliczY (int yr) {
        double wynik = (yr - ymin)*skala + margines;
        return (int)wynik;
    }
    
    private void ustawRzeczy (BufferedReader wejscie, BufferedReader wyjscie) throws IOException {
        
        String linia;
        
        // Wczytanie listy miast, znalezienie skrajnych wsółrzędnych
        miasta = new ArrayList<Punkt>();        
        wejscie.readLine(); // pierwsza linia niepotrzebna        
        while (true) {
           linia = wejscie.readLine();
           if (linia == null) {
               break;
           }
           else {
               String[] wspolrzedne = linia.split(" ");
               Punkt p = new Punkt(wspolrzedne[0], wspolrzedne[1]);
               miasta.add(p);
               
               if (miasta.size() == 1) {
                   xmin = xmax = p.x;
                   ymin = ymax = p.y;
               }
               else
               {
                   if (p.x < xmin) {
                       xmin = p.x;
                   }
                   else if (p.x > xmax) {
                       xmax = p.x;
                   }
                   if (p.y < ymin) {
                       ymin = p.y;
                   }
                   else if (p.y > ymax) {
                       ymax = p.y;
                   }
               }
           }
        }
           
        //Wczytanie listy ścieżek
        sciezki = new ArrayList<ArrayList<Integer>>();
        wyjscie.readLine(); // pierwsza linia niepotrzebna  
        wyjscie.readLine(); // druga linia niepotrzebna   
        while (true) {
           linia = wyjscie.readLine();
           if (linia == null) {
               break;
           }
           else {
               ArrayList<Integer> nowaLista = new ArrayList<Integer>();
               for (String s : linia.split(" ")) {
                   nowaLista.add(Integer.parseInt(s));
               }
               sciezki.add(nowaLista);
           }
        }
        
        //Wyliczenie skali
        skala = (double)szerokosc/(double)(xmax - xmin);
        double skala2 = (double)wysokosc/(double)(ymax - ymin);
        if (skala2 < skala) {
            skala = skala2;
        }
    }

    public PanelRysowania(BufferedReader wejscie, BufferedReader wyjscie) throws IOException {
        
        margines = 5;   
        setSize(800, 600);
        ustawRzeczy(wejscie, wyjscie);
        
    }
    
    @Override
    public void setSize (int width, int height) {
        super.setSize(width, height);
        wysokosc = height - 2*margines;
        szerokosc = width - 2*margines;
        
        
    }
    @Override
    public void paint(Graphics g) {
        
        g.setColor(Color.white);
        g.fillRect(0, 0, szerokosc + 2*margines, wysokosc + 2*margines);
        
        Color kolor;
        int red = 255;
        int green = 0;
        int blue = 0;
        
        for (ArrayList<Integer> s : sciezki) {
            
            // Zmiana koloru linii
            red = (red+150)%255;
            green = (green+50)%255;
            blue = (blue+10)%255;
            kolor = new Color(red, green, blue);
            g.setColor(kolor);
            
            // Rysowanie ścieżki           
            for (int i=0; i<(s.size()-1); ++i) {
                int x1 = miasta.get(s.get(i)).x;
                int y1 = miasta.get(s.get(i)).y;
                int x2 = miasta.get(s.get(i+1)).x;
                int y2 = miasta.get(s.get(i+1)).y;
                g.drawLine(przeliczX(x1), przeliczY(y1), przeliczX(x2), przeliczY(y2));
            }
        }
        
        g.setColor(Color.blue);
        for (Punkt p : miasta) {
            g.fillRect(przeliczX(p.x)-2, przeliczY(p.y)-2, 5, 5);
            g.setColor(Color.red);            
        }
        
    }

    void zapisz(String text) {
        try {
            BufferedImage bi = new BufferedImage(getWidth(), getHeight(), BufferedImage.TYPE_INT_RGB);
            Graphics2D g = bi.createGraphics();
            paint(g);
            ImageIO.write(bi, "png", new File(text));
        }
        catch (Exception e) {          
        }
    }
        
}
