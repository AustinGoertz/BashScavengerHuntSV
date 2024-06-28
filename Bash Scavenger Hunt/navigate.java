import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

class Navigate {

    public static boolean exists(String directory, String file) {
        File file_object = new File(directory, file);
        return file_object.exists();
    }

    public static boolean directoryStructureValid() {
        String programDirectory = System.getProperty("user.dir");

        File directory = new File(programDirectory);

        // Get the list of files in the directory
        File[] files = directory.listFiles();
        int numberOfFiles = files != null ? files.length : 0;
        return numberOfFiles == 3;
    }

    public static void writeBashScript(List<String> planets, String fileName) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
            writer.write("#!/bin/bash\n\n");
            writer.write("# Create the main directory\n");
            writer.write("mkdir -p Planets\n\n");
    
            for (String planet : planets) {
                writer.write("mkdir -p \"planets/" + planet + "\"\n");
                if (planet.equals("TRAPPIST-1_f")) {
                    writer.write("touch \"planets/TRAPPIST-1_f/correct.txt\"\n");
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void writeCluesTxt() {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter("clues.txt"))) {
            writer.write("CLUE 1: The planet we are looking for is not in a part of the HD catalogue and was not discovered by the Kepler telescope.\n");
            writer.write("       Recall that the \"-v\" flag with grep is used to negate a search, or in other words, asks the question \"what is everything that is not ...?\"\n\n");
            writer.write("CLUE 2: The planet we are looking for is the fifth planet away from its star. Think about what letter this will correspond to.\n\n");
            writer.write("CLUE 3: The planet we are looking was discovered by the TRAnsiting Planets and PlanetesImals Small Telescope. If you think you know which planet we are looking for, change the directory to this planet.\n");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String args[]) {
        if (args.length != 2) {
            System.out.println("ERROR: Invalid number of command line arguments.");
            System.exit(1);
        } else if (!directoryStructureValid()) {
            System.out.println("ERROR: Directory Structure Invalid.");
            System.out.println("");
            System.exit(1);
        } else if (!exists(args[0], ".FuelUpOrderCheck")) {
            System.out.println(args[0]);
            System.out.println("ERROR: No fuel in ship.");
            System.out.println("Check directory for fuel in first CLA spot, and ensure the probe has fuel.");
            System.exit(1);
        } else if (!exists(args[1], ".CheckLaunchOrder")) {
            System.out.println("ERROR: Ship is not launched.");
            System.out.println("Check directory for fuel in second CLA spot, and ensure the ship has been launched.");
            System.exit(1);
        } else {
            List<String> planets = Arrays.asList(
                    "HD_189733_b", "51_Pegasi_b", "Kepler-22_b", "Proxima_Centauri_b", "Gliese_581_g",
                    "TRAPPIST-1_d", "HD_209458_b", "WASP-12_b", "Kepler-452_b", "Kepler-16_b",
                    "HD_40307_g", "GJ_1214_b", "Kepler-10_c", "Gliese_667_Cc", "Kepler-62_f",
                    "Gliese_436_b", "HD_85512_b", "Gliese_876_d", "HD_69830_d", "Kepler-11_f",
                    "55_Cancri_e", "Kepler-442_b", "HD_106906_b", "Kepler-69_c", "HD_149026_b",
                    "Gliese_832_c", "Kepler-20_e", "HD_189567_c", "Kepler-37_b", "Gliese_3470_b",
                    "HD_10180_c", "HD_209458_c", "Kepler-186_f", "Kepler-62_e", "Gliese_1214_b",
                    "HD_219134_b", "Gliese_581_d", "HD_40307_b", "HD_189733_c", "Kepler-22_c",
                    "WASP-17_b", "Kepler-442_c", "HD_108874_b", "Gliese_163_c", "HD_125612_c",
                    "Kepler-20_b", "Gliese_667_Cf", "HD_20782_b", "Gliese_581_c", "HD_102365_b",
                    "Kepler-90_i", "HD_156668_b", "HD_115617_c", "Kepler-296_e", "HD_189733_d",
                    "Gliese_876_b", "HD_69830_b", "Kepler-11_b", "55_Cancri_c", "Kepler-442_d",
                    "HD_106906_c", "Kepler-69_b", "HD_149026_c", "Gliese_832_d", "Kepler-20_c",
                    "HD_189567_d", "Kepler-37_c", "Gliese_3470_c", "HD_10180_d", "HD_209458_d",
                    "Kepler-186_c", "Kepler-62_d", "Gliese_1214_c", "HD_219134_c", "Gliese_581_e",
                    "HD_40307_c", "HD_189733_e", "Kepler-22_d", "WASP-17_c", "Kepler-442_e",
                    "HD_108874_c", "Gliese_163_d", "HD_125612_d", "Kepler-20_d", "Gliese_667_Cd",
                    "HD_20782_c", "Gliese_581_f", "HD_102365_c", "Kepler-90_j", "HD_156668_c",
                    "HD_115617_d", "Kepler-296_f", "HD_189733_f", "Gliese_876_c", "HD_69830_c",
                    "Kepler-11_c", "55_Cancri_d", "Kepler-442_f", "HD_106906_d", "Kepler-69_d",
                    "Kepler-47_c", "WASP-39_b", "HD_37605_b", "Kepler-22_e", "HD_189733_g",
                    "Gliese_504_b", "HD_95086_b", "Kepler-48_b", "HD_149026_d", "Kepler-105_c",
                    "Kepler-62_c", "HD_37605_c", "Kepler-47_d", "WASP-12_c", "Kepler-20_f",
                    "Gliese_163_e", "HD_106906_e", "Kepler-69_e", "Kepler-90_k", "HD_115617_e",
                    "Kepler-296_g", "HD_40307_d", "Gliese_876_e", "Kepler-442_g", "HD_209458_e",
                    "Kepler-442_h", "Gliese_581_h", "HD_189733_h", "Kepler-90_l", "Kepler-69_f",
                    "HD_106906_f", "Gliese_667_Ce", "Kepler-20_g", "HD_102365_d", "Kepler-37_d",
                    "Kepler-296_h", "HD_40307_e", "Gliese_832_e", "Kepler-22_f", "WASP-17_d",
                    "Kepler-442_i", "HD_108874_d", "Gliese_163_f", "HD_125612_e", "Kepler-20_h",
                    "Gliese_3470_d", "HD_20782_d", "Gliese_876_f", "HD_69830_e", "Kepler-11_d",
                    "55_Cancri_f", "Kepler-442_j", "HD_106906_g", "Kepler-69_g", "HD_149026_e",
                    "Gliese_504_c", "HD_95086_c", "Kepler-48_c", "HD_37605_d", "Kepler-47_e",
                    "WASP-12_d", "Kepler-20_i", "Gliese_163_g", "HD_106906_h", "Kepler-69_h",
                    "Kepler-90_m", "HD_115617_f", "Kepler-296_i", "HD_40307_f", "Gliese_876_g",
                    "Kepler-442_k", "HD_209458_f", "Kepler-442_l", "Gliese_581_i", "HD_189733_i",
                    "Kepler-90_n", "Kepler-69_i", "HD_106906_i", "Gliese_667_Cg", "Kepler-20_j",
                    "HD_102365_e", "Kepler-37_e", "Kepler-296_j", "HD_40307_g", "Gliese_832_f",
                    "Kepler-22_g", "WASP-17_e", "Kepler-442_m", "HD_108874_e", "Gliese_163_h",
                    "Proxima_Centauri_c", "LHS_1140_b", "Kepler-442_n", "TRAPPIST-1_e", "K2-72_e",
                    "K2-72_f", "Kepler-438_b", "Kepler-1229_b", "Kepler-186_f", "LHS_1140_c",
                    "Proxima_Centauri_d", "LHS_1140_d", "Kepler-442_o", "TRAPPIST-1_f", "K2-72_g",
                    "Earth"
            );

            Collections.shuffle(planets);
            writeBashScript(planets, "downloadPlanets.sh");
            writeCluesTxt();

            System.out.println();
            System.out.println("Navigation Data Downloaded in current directory; please move downloadPlanets.sh and clues.txt to home directory.");
            System.out.println("Now, you must give yourself permission to run this script. Recall the chmod command.");
            System.out.println("Run the script by running ./downloadPlanets.sh");
            System.out.println("Navigate to the Earth directory in Planets for your first clue.");
            System.out.println();
        }
    }
}

    