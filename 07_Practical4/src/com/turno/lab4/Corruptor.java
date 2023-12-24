package com.turno.lab4;

import java.util.ArrayList;
import java.util.Random;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Corruptor {

    Random random = new Random();

    String stringToCorrupt;
    ArrayList<Integer> possiblePositionsToCorrupt = new ArrayList<>();
    Pattern pattern = Pattern.compile("[+-]5V");
    Matcher matcher;

    Corruptor(String stringToCorrupt) {
        this.stringToCorrupt = stringToCorrupt;
    }

    String getCorruptedString(boolean undetectableFlag) {

        String corruptedString = stringToCorrupt;

        if (!undetectableFlag) {

            matcher = pattern.matcher(stringToCorrupt);

            while (matcher.find()) {
                possiblePositionsToCorrupt.add(matcher.start());
            }

            int corruptIndex = possiblePositionsToCorrupt.get(random.nextInt(possiblePositionsToCorrupt.size()));

            char[] mutableString = stringToCorrupt.toCharArray();
            mutableString[corruptIndex] = (mutableString[corruptIndex] == '+') ? '-' : '+';

            if (corruptIndex % 2 == 0) {
                mutableString[corruptIndex + 5] = (mutableString[corruptIndex + 5] == '+') ? '-' : '+';
            } else {
                mutableString[corruptIndex - 5] = (mutableString[corruptIndex - 5] == '+') ? '-' : '+';
            }

            corruptedString = new String(mutableString);

        } else {

            try {

                String temp = Processor.manchesterDecoding(stringToCorrupt);
                int corruptIndex = random.nextInt(temp.length());

                int selectedRow = corruptIndex / 9;
                int selectedColumn = corruptIndex % 9;

                int totalRow = (temp.length() / 9) + 1;
                int totalColumn = 9;

                int selectedRowAlt;
                int selectedColumnAlt;

                do {
                    selectedRowAlt = random.nextInt(totalRow);
                } while (selectedRowAlt == selectedRow);

                do {
                    selectedColumnAlt = random.nextInt(totalColumn);
                } while (selectedColumnAlt == selectedColumn);

                char[] mutableString = temp.toCharArray();
                mutableString[selectedRow * 9 + selectedColumn] = (mutableString[selectedRow * 9 + selectedColumn] == '0' ? '1' : '0');
                mutableString[selectedRow * 9 + selectedColumnAlt] = (mutableString[selectedRow * 9 + selectedColumnAlt] == '0' ? '1' : '0');
                mutableString[selectedRowAlt * 9 + selectedColumn] = (mutableString[selectedRowAlt * 9 + selectedColumn] == '0' ? '1' : '0');
                mutableString[selectedRowAlt * 9 + selectedColumnAlt] = (mutableString[selectedRowAlt * 9 + selectedColumnAlt] == '0' ? '1' : '0');

                corruptedString = Processor.manchesterEncoding(new String(mutableString));

            } catch (Exception e) {
                System.out.println("[Corruptor] Invalid string.");
            }
        }

        return corruptedString;

    }
}
