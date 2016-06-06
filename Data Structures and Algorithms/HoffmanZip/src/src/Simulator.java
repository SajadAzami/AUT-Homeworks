/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package src;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import static java.lang.Thread.MIN_PRIORITY;
import java.nio.ByteBuffer;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JOptionPane;
import sun.security.util.BitArray;

/**
 *
 * @author Sajad Azami
 */
public class Simulator {

    byte[] lines = null;
    byte[] readlines = null;
    ArrayList<Byte> readlinesList = new ArrayList<>();
    BST bst;
    ArrayList<Byte> values = new ArrayList<>();
    ArrayList<Byte> bytes = new ArrayList<>();
    ArrayList<Integer> keys = new ArrayList<>();
    ArrayList<Byte> charCopy = new ArrayList<>();
    ArrayList<ArrayList<Boolean>> code; //Code for each value at index of values

    public boolean process(String address) {
        //ZIP
        if (!address.endsWith("txt")) {
            JOptionPane.showMessageDialog(null, "Please choose a text file!", "No TextFile Found", MIN_PRIORITY);
            return false;
        }
        try {
            lines = Files.readAllBytes(Paths.get(address));
        } catch (IOException ex) {
            Logger.getLogger(Simulator.class.getName()).log(Level.SEVERE, null, ex);
        }
        bytes = new ArrayList<>();
        for (int i = 0; i < lines.length; i++) {
            bytes.add(lines[i]);
        }
        for (int i = 0; i < bytes.size(); i++) {
            charCopy.add(bytes.get(i));
        }
//        bytes.remove(0);
//        bytes.remove(0);
//        bytes.remove(0);
//        charCopy.remove(0);
//        charCopy.remove(0);
//        charCopy.remove(0);
        for (int i = 0; i < bytes.size(); i++) {
            if (values.contains(bytes.get(i))) {
                keys.set(values.indexOf(bytes.get(i)), keys.get(values.indexOf(bytes.get(i))) + 1);
            } else {
                keys.add(1);
                values.add(bytes.get(i));
            }
        }
        bst = new BST(values, keys);

        code = new ArrayList<>();
        for (int i = 0; i < values.size(); i++) {
            code.add(bst.generateCode(values.get(i)));
        }
        ArrayList<Boolean> bigBools = new ArrayList<>();
        for (int i = 0; i < charCopy.size(); i++) {
            for (int k = 0; k < values.size(); k++) {
                if (charCopy.get(i).equals(values.get(k))) {
                    for (int j = 0; j < code.get(k).size(); j++) {
                        bigBools.add(code.get(k).get(j));
                    }
                    break;
                }
            }
        }
        boolean[] bigBoolsArray = new boolean[bigBools.size()];
        for (int i = 0; i < bigBools.size(); i++) {
            bigBoolsArray[i] = bigBools.get(i);
        }
        BitArray bigBitArray = new BitArray(bigBoolsArray);
        try {
            FileOutputStream out = new FileOutputStream("Coded.txt");
            try {
                out.write(bigBitArray.toByteArray());
                out.close();
            } catch (IOException ex) {
                Logger.getLogger(Simulator.class.getName()).log(Level.SEVERE, null, ex);
            }
        } catch (FileNotFoundException ex) {
            Logger.getLogger(Simulator.class.getName()).log(Level.SEVERE, null, ex);
        }

        //UNZIP
        if (!address.endsWith("txt")) {
            JOptionPane.showMessageDialog(null, "Please choose a text file!", "No TextFile Found", MIN_PRIORITY);
            return false;
        }
        try {
            readlines = Files.readAllBytes(Paths.get("Coded.txt"));
        } catch (IOException ex) {
            Logger.getLogger(Simulator.class.getName()).log(Level.SEVERE, null, ex);
        }
        boolean[] temp = new boolean[8];
        ArrayList<Boolean> bigBoolDecode = new ArrayList<>();
        for (int i = 0; i < readlines.length; i++) {
            temp[0] = ((readlines[i] & 0x01) != 0);
            temp[1] = ((readlines[i] & 0x02) != 0);
            temp[2] = ((readlines[i] & 0x04) != 0);
            temp[3] = ((readlines[i] & 0x08) != 0);
            temp[4] = ((readlines[i] & 0x10) != 0);
            temp[5] = ((readlines[i] & 0x20) != 0);
            temp[6] = ((readlines[i] & 0x40) != 0);
            temp[7] = ((readlines[i] & 0x80) != 0);
            for (int j = 0; j < 8; j++) {
                bigBoolDecode.add(temp[j]);
            }
        }
        ArrayList<Boolean> decoderLast = new ArrayList<>();
        ArrayList<Integer> indexes = new ArrayList<>();
        ArrayList<Boolean> tester = new ArrayList<>();
        for (int i = 0; i < bigBools.size(); i++) {
            decoderLast.add(bigBools.get(i));
        }
        int count = decoderLast.size();
        for (int i = 0; i < count; i++) {
            tester.add(decoderLast.get(0));
            decoderLast.remove(0);
            if (code.contains(tester)) {
                indexes.add(code.indexOf(tester));
                tester.clear();
            }
        }
        byte[] toWriteArray = new byte[indexes.size()];
        for (int i = 0; i < indexes.size(); i++) {
            toWriteArray[i] = values.get(indexes.get(i));
        }
        try {
            FileOutputStream out = new FileOutputStream("Decoded.txt");
            try {
                out.write(toWriteArray);
                out.close();
            } catch (IOException ex) {
                Logger.getLogger(Simulator.class.getName()).log(Level.SEVERE, null, ex);
            }
        } catch (FileNotFoundException ex) {
            Logger.getLogger(Simulator.class.getName()).log(Level.SEVERE, null, ex);
        }
        return true;
    }

}
