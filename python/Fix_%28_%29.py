import os
import re


def replace_percent_encoding(directory):
    # Define the regular expression pattern for "%28" and "%29"
    pattern = re.compile(r'%28|%29')

    # Walk through the directory recursively
    for root, dirs, files in os.walk(directory):
        for file_name in files:
            # Construct the full path to the file
            file_path = os.path.join(root, file_name)

            # Perform the substitution on the file name
            new_file_name = pattern.sub(lambda match: '(' if match.group() == '%28' else ')', file_name)

            # Construct the full path to the new file name
            new_file_path = os.path.join(root, new_file_name)

            # Rename the file if the new file name is different
            if file_name != new_file_name:
                os.rename(file_path, new_file_path)
                print(f'Renamed: {file_path} -> {new_file_path}')


if __name__ == "__main__":
    # Replace 'your_directory_path' with the actual path to the directory
    directory_path = 'C:/Users/10sta/GoogleDrive/Four Boards/Website New/fourboards/images'

    replace_percent_encoding(directory_path)
