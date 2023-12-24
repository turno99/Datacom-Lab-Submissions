package com.turno.lab4;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.concurrent.atomic.AtomicBoolean;

public class Processor {

    // Store the previous voltage level and odd/even count
    static AtomicBoolean prevNonZero = new AtomicBoolean();
    static AtomicBoolean isNonZeroEven = new AtomicBoolean(true);

    // Checks the integrity of the bitstream
    private static boolean bitStreamIntegrity(String bitStream) {

        int bitStreamSize = bitStream.length();

        for (int idx = 0; idx < bitStreamSize; idx++) {
            if (bitStream.charAt(idx) != '0' && bitStream.charAt(idx) != '1') {
                return false;
            }
        }

        return true;

    }

    public static String manchesterEncoding(String bitStream) throws Exception {

        if (!bitStreamIntegrity(bitStream)) {
            throw new Exception("Invalid bitstream.");
        }

        int bitStreamLength = bitStream.length();
        StringBuilder encodedString = new StringBuilder();

        for (int idx = 0; idx < bitStreamLength; idx++) {

            if (bitStream.charAt(idx) == '0') {
                encodedString.append("+5V, -5V");
            } else {
                encodedString.append("-5V, +5V");
            }

            if (idx != bitStreamLength - 1) {
                encodedString.append(", ");
            }

        }

        return encodedString.toString();

    }

    public static String manchesterDecoding(String encodedString) throws Exception {

        // Split the string into individual voltage levels
        encodedString = encodedString.replace(" ", "").toUpperCase();
        ArrayList<String> voltages = new ArrayList<>(Arrays.asList(encodedString.split(",")));

        int voltagesSize = voltages.size();
        StringBuilder decodedString = new StringBuilder();

        // Check voltage level integrity
        for (String voltage : voltages) {
            if (!voltage.equals("+5V") && !voltage.equals("-5V")) {
                throw new Exception("Invalid voltage level.");
            }
        }

        for (int idx = 0; idx < voltagesSize; idx += 2) {
            if ((idx + 1 < voltagesSize) && voltages.get(idx).equals(voltages.get(idx + 1))) {
                throw new Exception("Invalid sequence.");
            }

            if (voltages.get(idx).equals("+5V")) {
                decodedString.append('0');
            } else {
                decodedString.append('1');
            }
        }

        return decodedString.toString();

    }

    // Encodes the bitstream in HDB3
    public static String HDB3Encoding(String bitStream) throws Exception {

        if (!bitStreamIntegrity(bitStream)) {
            throw new Exception("Invalid bitstream.");
        }

        ArrayList<String> voltages = new ArrayList<>(); // Stores individual voltage levels
        StringBuilder encodedStream = new StringBuilder();
        int zeroCount = 0;
        int cycles, rem;
        int bitStreamSize = bitStream.length();

        for (int idx = 0; idx < bitStreamSize; idx++) {
            if (bitStream.charAt(idx) == '0') {
                if (zeroCount == 4) { // Pattern matching
                    if (isNonZeroEven.get()) {
                        voltages.addAll(Arrays.asList(prevNonZero.get() ? "-5V" : "+5V", "0V", "0V", prevNonZero.get() ? "-5V" : "+5V")); // B00V
                        prevNonZero.set(!prevNonZero.get());
                    } else {
                        voltages.addAll(Arrays.asList("0V", "0V", "0V", prevNonZero.get() ? "+5V" : "-5V")); // 000V
                        isNonZeroEven.set(!isNonZeroEven.get());
                    }
                    zeroCount = 1; // Adds the next zero
                } else {
                    zeroCount++; // Increments the number of zeroes
                }
            } else {
                if (zeroCount == 4) { // Pattern matching
                    if (isNonZeroEven.get()) {
                        voltages.addAll(Arrays.asList(prevNonZero.get() ? "-5V" : "+5V", "0V", "0V", prevNonZero.get() ? "-5V" : "+5V")); // B00V
                        prevNonZero.set(!prevNonZero.get());
                    } else {
                        voltages.addAll(Arrays.asList("0V", "0V", "0V", prevNonZero.get() ? "+5V" : "-5V")); // 000V
                        isNonZeroEven.set(!isNonZeroEven.get());
                    }
                    zeroCount = 0;
                } else {
                    while (zeroCount != 0) { // Normal 0V handling
                        voltages.add("0V");
                        zeroCount--;
                    }
                }
                voltages.add(prevNonZero.get() ? "-5V" : "+5V");
                prevNonZero.set(!prevNonZero.get());
                isNonZeroEven.set(!isNonZeroEven.get());
            }
        }

        // Empty remaining voltages
        cycles = zeroCount / 4;
        rem = zeroCount % 4;

        while (cycles != 0) {
            if (isNonZeroEven.get()) {
                voltages.addAll(Arrays.asList(prevNonZero.get() ? "-5V" : "+5V", "0V", "0V", prevNonZero.get() ? "-5V" : "+5V"));
                prevNonZero.set(!prevNonZero.get());
            } else {
                voltages.addAll(Arrays.asList("0V", "0V", "0V", prevNonZero.get() ? "+5V" : "-5V"));
                isNonZeroEven.set(!isNonZeroEven.get());
            }
            cycles--;
        }

        while (rem != 0) {
            voltages.add("0V");
            rem--;
        }

        // Build the encoded stream
        for (int idx = 0; idx < voltages.size(); idx++) {

            encodedStream.append(voltages.get(idx));

            if (idx != bitStreamSize - 1) {
                encodedStream.append(", ");
            }
        }

        return encodedStream.toString();
    }

    public static String HDB3Decoding(String encodedString) throws Exception {

        // Split the string into individual voltage levels
        encodedString = encodedString.replace(" ", "").toUpperCase();
        ArrayList<String> voltages = new ArrayList<>(Arrays.asList(encodedString.split(",")));

        // Check voltage level integrity
        for (String voltage : voltages) {
            if (!voltage.equals("+5V") && !voltage.equals("0V") && !voltage.equals("-5V")) {
                throw new Exception("Invalid voltage level.");
            }
        }

        int voltagesSize = voltages.size();
        StringBuilder bitStream = new StringBuilder();

        for (int idx = 0; idx < voltagesSize; idx++) {
            if ((idx + 3) < voltagesSize) {
                if (prevNonZero.get()) {
                    if (isNonZeroEven.get()) {
                        if (voltages.get(idx).equals("-5V") && voltages.get(idx + 1).equals("0V") && voltages.get(idx + 2).equals("0V") && voltages.get(idx + 3).equals("-5V")) { // B00V
                            bitStream.append("0000");
                            idx += 3;
                            isNonZeroEven.set(true);
                            prevNonZero.set(!prevNonZero.get());
                            continue;
                        }
                    } else {
                        if (voltages.get(idx).equals("0V") && voltages.get(idx + 1).equals("0V") && voltages.get(idx + 2).equals("0V") && voltages.get(idx + 3).equals("+5V")) { // 000V
                            bitStream.append("0000");
                            idx += 3;
                            isNonZeroEven.set(true);
                            continue;
                        }
                    }
                } else {
                    if (isNonZeroEven.get()) {
                        if (voltages.get(idx).equals("+5V") && voltages.get(idx + 1).equals("0V") && voltages.get(idx + 2).equals("0V") && voltages.get(idx + 3).equals("+5V")) { // B00V
                            bitStream.append("0000");
                            idx += 3;
                            isNonZeroEven.set(true);
                            prevNonZero.set(!prevNonZero.get());
                            continue;
                        }
                    } else {
                        if (voltages.get(idx).equals("0V") && voltages.get(idx + 1).equals("0V") && voltages.get(idx + 2).equals("0V") && voltages.get(idx + 3).equals("-5V")) { // 000V
                            bitStream.append("0000");
                            idx += 3;
                            isNonZeroEven.set(true);
                            continue;
                        }
                    }
                }
            }
            if (voltages.get(idx).equals("0V")) {
                bitStream.append('0');
            } else if ((voltages.get(idx).equals("+5V") && prevNonZero.get()) || (voltages.get(idx).equals("-5V") && !prevNonZero.get())) {
                throw new Exception("Violation detected besides the pattern.");
            } else if (voltages.get(idx).equals("+5V") || voltages.get(idx).equals("-5V")) {
                bitStream.append('1');
                prevNonZero.set(!prevNonZero.get());
                isNonZeroEven.set(!isNonZeroEven.get());
            } else {
                throw new Exception("Invalid voltage level.");
            }
        }

        return bitStream.toString();

    }

    public static String parityGenerator(String bitStream) throws Exception {

        // Check bitstream integrity
        if (!bitStreamIntegrity(bitStream)) {
            throw new Exception("Invalid bitstream");
        }

        int bitStreamSize = bitStream.length();
        ArrayList<String> bytes = new ArrayList<>();
        StringBuilder parityPrint = new StringBuilder();

        if (bitStreamSize % 8 != 0) {
            throw new Exception("Bitstream should be divisible by 8.");
        }

        // Row parity generation

        for (int idx = 0; idx < bitStreamSize; idx += 8) {
            String currentByte = bitStream.substring(idx, idx + 8);
            parityPrint.append(currentByte);
            long oneCount = currentByte.chars().filter(ch -> ch == '1').count();
            char appendChar = (oneCount % 2 == 0) ? '0' : '1';

            parityPrint.append('|');
            parityPrint.append(appendChar);
            parityPrint.append("\n");

            currentByte += appendChar;
            bytes.add(currentByte);
        }

        // Column parity generation

        StringBuilder columnParityString = new StringBuilder();

        for (int charPosition = 0; charPosition < 9; charPosition++) {

            StringBuilder column = new StringBuilder();

            for (String currentByte : bytes) {
                column.append(currentByte.charAt(charPosition));
            }

            long columnOneCount = column.chars().filter(ch -> ch == '1').count();
            columnParityString.append((columnOneCount % 2 == 0) ? '0' : '1');
        }

        // Parity representation
        parityPrint.append("__________\n");
        parityPrint.append(columnParityString.toString(), 0, columnParityString.length() - 1);
        parityPrint.append('|');
        parityPrint.append(columnParityString.toString().charAt(columnParityString.length() - 1));
        System.out.println(parityPrint.toString());

        return String.join("", bytes) + columnParityString.toString();

    }

    public static String parityChecker(String bitStream) throws Exception {

        // Check bitstream integrity
        if (!bitStreamIntegrity(bitStream)) {
            throw new Exception("Invalid bitstream");
        }

        int bitStreamSize = bitStream.length();
        ArrayList<String> bytes = new ArrayList<>();
        ArrayList<String> byteStripped = new ArrayList<>();
        StringBuilder parityPrint = new StringBuilder();

        // Row parity check

        for (int idx = 0; idx < bitStreamSize - 9; idx += 9) {

            String currentByte = bitStream.substring(idx, idx + 8);
            byteStripped.add(currentByte);

            parityPrint.append(currentByte);
            parityPrint.append("|");
            parityPrint.append(bitStream.charAt(idx + 8));
            parityPrint.append("\n");

            long oneCount = currentByte.chars().filter(ch -> ch == '1').count();
            currentByte += (oneCount % 2 == 0) ? "0" : "1";
            if (!currentByte.equals(bitStream.substring(idx, idx + 9))) {
                throw new Exception("Error detected at row " + (idx + 1));
            }
            bytes.add(currentByte);
        }

        // Parity representation
        parityPrint.append("__________\n");
        parityPrint.append(bitStream, bitStreamSize - 9, bitStreamSize - 1);
        parityPrint.append('|');
        parityPrint.append(bitStream.charAt(bitStreamSize - 1));
        System.out.println(parityPrint.toString());

        // Column parity check

        StringBuilder columnParityStringBuilder = new StringBuilder();

        for (int charPosition = 0; charPosition < 9; charPosition++) {

            StringBuilder column = new StringBuilder();

            for (String currentByte : bytes) {
                column.append(currentByte.charAt(charPosition));
            }

            long columnOneCount = column.chars().filter(ch -> ch == '1').count();
            columnParityStringBuilder.append((columnOneCount % 2 == 0) ? '0' : '1');
        }

        String columnParityString = columnParityStringBuilder.toString();

        for (int idx = 0; idx < 9; idx++) {
            if (columnParityString.charAt(idx) != bitStream.charAt(bitStreamSize - 9 + idx)) {
                throw new Exception("Error detected at column " + (idx + 1));
            }
        }

        return String.join("", byteStripped);

    }
}
