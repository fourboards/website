import os
from pathlib import Path

def change_extensions_to_lowercase(folder_path):
    # Check if the folder path exists
    if not os.path.exists(folder_path):
        print(f"Error: Folder '{folder_path}' does not exist.")
        return

    # Iterate through all files and subdirectories in the folder
    for root, dirs, files in os.walk(folder_path):
        for filename in files:
            file_path = os.path.join(root, filename)

            # Check if it's a file
            if os.path.isfile(file_path):
                # Split the filename and extension
                base_name, extension = os.path.splitext(filename)

                # Convert the extension to lowercase
                new_extension = extension.lower()

                # Rename the file with the new extension
                new_file_path = os.path.join(root, base_name + new_extension)
                os.rename(file_path, new_file_path)

                print(f"Renamed: {filename} -> {base_name + new_extension}")

if __name__ == "__main__":
    # Replace 'your_folder_path' with the path to the folder containing the files
    folder_path = Path("C:/Users/10sta/GoogleDrive/Four Boards/Website New/fourboards/images/")
    change_extensions_to_lowercase(folder_path)
