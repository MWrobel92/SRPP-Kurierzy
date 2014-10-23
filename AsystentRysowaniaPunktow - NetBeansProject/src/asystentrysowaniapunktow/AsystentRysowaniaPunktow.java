/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package asystentrysowaniapunktow;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.FileReader;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.JToolBar;

/**
 *
 * @author Michal
 */
public class AsystentRysowaniaPunktow extends JPanel implements ActionListener {
    
    JPanel panelGlowny;
    PanelRysowania rysunek;
    JButton zap;
    
    JTextField wej;
    JTextField wyj;
    JTextField rys;
    
    private static void przygotujIPokazGUI() {        
        
        JFrame.setDefaultLookAndFeelDecorated(true);
        JFrame frame = new JFrame("Kurier wizualizacja");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        //prepairing panel
        AsystentRysowaniaPunktow newContentPane = new AsystentRysowaniaPunktow();
        newContentPane.setOpaque(true); 
        frame.setContentPane(newContentPane);

        //showing window
        frame.pack();
        frame.setSize(810, 670);
        frame.setVisible(true);
    }
    
    private void zrobKontrolkeGlowna () {
        
        panelGlowny = new JPanel(); 
        panelGlowny.setLayout(new BorderLayout());
        
        try {
            BufferedReader wejscie = new BufferedReader (new FileReader(wej.getText()));
            BufferedReader wyjscie = new BufferedReader (new FileReader(wyj.getText()));
            
            rysunek = new PanelRysowania(wejscie, wyjscie);
            
            panelGlowny.add(rysunek);
            zap.setEnabled(true);
        }
        catch (Exception ex) {
            panelGlowny.add(new JLabel("Nie udało się poprawnie załadować danych!"));
            zap.setEnabled(false);
        }
        
        add(BorderLayout.CENTER, panelGlowny);
        validate();
        
    }
    /**
     * Konstruktor
     */
    public AsystentRysowaniaPunktow () {
        
        wej = new JTextField(10);
        wej.setText("input.txt");
        wyj = new JTextField(10);
        wyj.setText("solution.txt");
        rys = new JTextField(10);
        rys.setText("vizualization.png");
        JButton prz = new JButton("Ładuj pliki");
        prz.addActionListener(this);
        prz.setActionCommand("ŁadowanieDanych");
        zap = new JButton("Zapisz obraz");
        zap.addActionListener(this);
        zap.setActionCommand("ZapisanieWykresu");
        
        JToolBar pasekNarzedzi = new JToolBar();
        pasekNarzedzi.add(new JLabel(" Plik z danymi: "));
        pasekNarzedzi.add(wej);
        pasekNarzedzi.add(new JLabel(" Plik z rezultatem: "));
        pasekNarzedzi.add(wyj);
        pasekNarzedzi.add(prz);
        pasekNarzedzi.add(rys);
        pasekNarzedzi.add(zap);
        
        
              
        setLayout (new BorderLayout());
        add(BorderLayout.NORTH, pasekNarzedzi);
        zrobKontrolkeGlowna();
        
        
    }
   
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        javax.swing.SwingUtilities.invokeLater(new Runnable() {           
               @Override
               public void run() {
                    przygotujIPokazGUI();
                };

            });
        
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        switch (e.getActionCommand()){
            case "ŁadowanieDanych":
                zrobKontrolkeGlowna();
                break;
            case "ZapisanieWykresu":
                rysunek.zapisz(rys.getText());
                break;
        }
        
    }
}
