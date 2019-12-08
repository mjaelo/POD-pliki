package sample

import javafx.event.ActionEvent
import javafx.fxml.FXML
import javafx.scene.control.TextField
import javafx.scene.text.Text

import java.io.BufferedWriter
import java.io.FileWriter
import java.math.BigInteger
import java.util.ArrayList
import java.util.List
import java.util.concurrent.ThreadLocalRandom

class Controller {
    @FXML
    private Text txt, givep, giveq, giveM
    @FXML
    private TextField given, givepq, givex0
    String s = ""
    BigInteger M, n
    long p, q
    List<BigInteger> x = new ArrayList()
    int pq = 0, x0


    @FXML
    protected void givespq(ActionEvent event) {
        pq = Integer.parseInt(givepq.getText())
        pqgen()
    }


    @FXML
    protected void display(ActionEvent event) {
        p = q = 0
        n = 0
        s = ""
        //getting data
        get()
        //generating number
        generate(n)
    }


    void get() {
        try {
            n = new BigInteger(given.getText())
            x0 = Integer.parseInt(givex0.getText())
        } catch (Exception e) {
            s += "\n" + e.getMessage()
        }


        //p q wzglednie pierwsze


        // czyli gdy p/4 = coś z resztą 3
        // np. 7/4 = 1 r 3


    }

    BigInteger givex(BigInteger xi, BigInteger M) {
        BigInteger hej
        if (M < xi) {
            hej = (xi**2) % M
        } else {
            BigInteger ok = xi % M
            hej = (ok * ok) % M
        }
        return hej

    }

    void generate(BigInteger n) {
        //s="Xn+1 = Xn^2 mod M "+s;
        String s01 = ""
        BigInteger xi = x0
        int s0 = 0, s1 = 0
        for (BigInteger i = 0; i < n; i++) {
            if (i != 0)
                xi = givex(xi, M)
            //s += " " + xi
            if (xi % 2 == 0) {
                s0++
                s01 += "0"
            } else {
                s1++
                s01 += "1"
            }
        }
        txt.setText("0: " + s0 + ", 1: " + s1)
        try {
            String nazwa = "wynik.txt";
            nazwa = "n" + n + "x" + x0 + "M" + M + "_0_" + s0 + "_1_" + s1 + ".txt";
            BufferedWriter writer = new BufferedWriter(new FileWriter(nazwa))
            writer.write(s01)
            writer.close()
        }
        catch (Exception e) {
            txt.setText(e.toString())
        }
    }

    void pqgen() {
        // p = 1;// p mod M = 3 mod 4
        // q = 1;// q mod M = 3 mod 4

        boolean ok = false
        while (!ok) {
            p = ThreadLocalRandom.current().nextInt(pq) + 1
            q = ThreadLocalRandom.current().nextInt(pq) + 1

            ok = false
            if (p % 4 == 3 && q % 4 == 3)
                ok = true
            /*
            ok = true
            for (int j = 2; j <= p; j++) {
                if (p % j == 0 && q % j == 0) ok = false
            }*/
        }
        givep.setText(p + "")
        giveq.setText(q + "")

        BigInteger tp = p
        BigInteger tq = q
        M = tp.multiply(tq)// M-1 to max numer.
        //teraz M = 77, wiec wartosc jest miedzy 0-76
        giveM.setText(M + "")
    }

}
