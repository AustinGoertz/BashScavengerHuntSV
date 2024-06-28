import time
import sys
import os

def check_directory_contents():
    # Get the current directory
    current_directory = os.getcwd()

    # List all files and directories in the current directory
    files_in_directory = os.listdir(current_directory)

    # Check if there are only two items in the directory
    if len(files_in_directory) != 2:
        print("Too many files in the directory.")
        return False

    # Check if both files are the Python script and the text file
    if "fuel_up.py" not in files_in_directory or "fuel.txt" not in files_in_directory:
        print("Missing a required file in current working directory.")
        return False

    return True


def progress_bar(duration):
    total_steps = 50  # Number of steps in the progress bar
    interval = duration / total_steps  # Time per step

    for i in range(total_steps + 1):
        percent = (i / total_steps) * 100
        bar = ('#' * i).ljust(total_steps)
        sys.stdout.write(f'\r[{bar}] {percent:.2f}%')
        sys.stdout.flush()
        time.sleep(interval)

    # Ensure the cursor moves to a new line after completion
    print()

def main():
    if(check_directory_contents() == False):
        sys.exit(1)
    progress_bar(5)
    print("Fuel Percentage: 100%")
    print("Move to prelaunch checklist.")
    open('.FuelUpOrderCheck', 'w')

if __name__ == "__main__":
    main()