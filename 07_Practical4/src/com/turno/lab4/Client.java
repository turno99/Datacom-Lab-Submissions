package com.turno.lab4;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.Scanner;

public class Client {

    Socket clientSocket = null;
    DataOutputStream outputStream = null;
    DataInputStream inputStream = null;
    Scanner scanner;

    public Client(String address, int port) {

        // Take user input via console
        scanner = new Scanner(System.in);

        try {

            // Create a new socket and attempt to connect to the server
            clientSocket = new Socket(address, port);

            // Create the streams required for data transfer
            outputStream = new DataOutputStream(clientSocket.getOutputStream());
            inputStream = new DataInputStream(clientSocket.getInputStream());

            String input;
            String encodedString;
            String response;

            Corruptor corruptor;

            while (true) {

                // Last voltage level selection
//                System.out.println("[Client] Select last voltage level:\n(1) Negative\n(2) Positive");
//                String voltOpt = scanner.nextLine();
//                if (voltOpt.equals("1")) {
//                    Processor.prevNonZero.set(false);
//                } else if (voltOpt.equals("2")) {
//                    Processor.prevNonZero.set(true);
//                } else {
//                    System.out.println("[Client] Invalid option. Default option selected: Negative");
//                    Processor.prevNonZero.set(false);
//                }
//
//                outputStream.writeBoolean(Processor.prevNonZero.get());
//                outputStream.flush();

                // Last non-zero level selection (odd/even)
//                System.out.println("[Client] Select whether last non-zero levels are odd/even:\n(1) Even\n(2) Odd");
//                String evenOpt = scanner.nextLine();
//                if (evenOpt.equals("1")) {
//                    Processor.isNonZeroEven.set(true);
//                } else if (evenOpt.equals("2")) {
//                    Processor.isNonZeroEven.set(false);
//                } else {
//                    System.out.println("[Client] Invalid option. Default option selected: Even");
//                    Processor.prevNonZero.set(true);
//                }
//
//                outputStream.writeBoolean(Processor.isNonZeroEven.get());
//                outputStream.flush();

                // Test corruption

                System.out.println("[Client] Test corruption?\n(1) No\n(2) Regular\n(3) Undetectable");
                String corruptOpt = scanner.nextLine();
                boolean enableCorruption;
                boolean undetectedFlag = false;

                switch (corruptOpt) {
                    case "1":
                        enableCorruption = false;
                        break;
                    case "2":
                        enableCorruption = true;
                        break;
                    case "3":
                        enableCorruption = true;
                        undetectedFlag = true;
                        break;
                    default:
                        System.out.println("[Client] Invalid option. Default option selected: No");
                        enableCorruption = false;
                        break;
                }

                System.out.println("[Client] Enter your input: ");
                input = scanner.nextLine();

                // Stop signal handling
                if (input.toUpperCase().equals("STOP")) {
                    outputStream.writeUTF(input);
                    outputStream.flush();
                    System.out.println("[Client] Service stopped.");
                    break;
                }

                try {

                    System.out.println("[Client] Given input: " + input);
                    System.out.println("[Client] Parity representation: ");
                    String parityPadded = Processor.parityGenerator(input);
                    encodedString = Processor.manchesterEncoding(parityPadded);

                    if (enableCorruption) {
                        corruptor = new Corruptor(encodedString);
                        encodedString = corruptor.getCorruptedString(undetectedFlag);
                    }

                    System.out.println("[Client] Encoded voltage levels: " + encodedString);

                } catch (Exception e) {
                    System.out.println("[ClientError] " + e.getMessage());
                    outputStream.writeUTF("ERROR");
                    continue;
                }

                // Send data to server after encoding
                System.out.println("[Client] Sending data to server...");
                outputStream.writeUTF(encodedString);
                System.out.println("[Client] Data sent.");
                outputStream.flush();
                response = inputStream.readUTF();
                System.out.println("[Client] Received data: " + response);

            }

            // Close the streams
            outputStream.close();
            clientSocket.close();

        } catch(IOException i) {
            System.out.println("[Client] Error connecting to server");
        }
    }

    public static void main(String[] args) {
        Client client = new Client("localhost", 8888);
    }
}
