import xml.etree.ElementTree as ET
from pathlib import Path
from web_pages import projects
from bs4 import BeautifulSoup

def process_html(html_in, filename):
    html_in = "".join([s for s in html_in.strip().splitlines(True) if s.strip()])

    soup = BeautifulSoup(html_in, 'html.parser')
    top_level_divs = soup.find_all('div', recursive=False)

    all_classes = set()
    html_out = ""

    for index, div in enumerate(top_level_divs, start=1):
        div_class = div.get('class', [])[0]
        all_classes.update([div_class])
        print(f"Top Level Div {index} Class: {div_class}")

        if div_class == "sqs-gallery-container" or div_class == "image-block-outer-wrapper":
            # Find all <img> tags within the current div
            images = div.find_all('img')
            unique_images = set()
            for image in images:
                image = image['src'].rsplit('/', 1)[-1]
                image = "{{ site.url }}/images/portfolio/" + filename + "/" + image
                unique_images.update([image])

            for image in unique_images:
                html_out = html_out + f'<img src="{image}">\n\n'

            print(f"Images in Div {index}: {unique_images}")

        elif div_class == "sqs-html-content":
            html_out = html_out + div.prettify()
            html_out = html_out + "\n\n"
            pass

    print(all_classes)

    return html_out



def extract_items_from_xml(xml_file):
    tree = ET.parse(xml_file)
    root = tree.getroot()

    for item in root.findall('.//item'):
        link_element = item.find('link')
        title_element = item.find('title')
        content_encoded_element = item.find('.//content:encoded',
                                                namespaces={'content': 'http://purl.org/rss/1.0/modules/content/'})

        # Check if both link and content elements exist
        if link_element is not None and content_encoded_element is not None and title_element is not None:
            link = link_element.text[1:]
            if link in projects:
                link = link
                title = title_element.text
                content_encoded = content_encoded_element.text
                content = process_html(content_encoded, link)


                # Create an HTML file with the link name
                html_filename = f"C:/Users/10sta/GoogleDrive/Four Boards/Website New/fourboards/_{projects[link]}/{link}.md"

                with open(html_filename, 'w', encoding='utf-8') as html_file:
                    # Write HTML content to the file

                    html_file.write("---\n")
                    html_file.write("layout: post\n")
                    html_file.write("hero-bg-color: '#FFFFFF'\n")
                    html_file.write(f"uid: {link}\n")
                    html_file.write(f"title:  '{title}'\n")
                    html_file.write(f"tags: portfolio\n")
                    html_file.write("---\n")
                    html_file.write("\n")
                    html_file.write(f"{content}")

                print(html_filename)
            else:
                print("Skipped item web address as link")
        else:
            print("Skipped item without link or content:encoded element.")


if __name__ == "__main__":
    xml_file_path = Path("export.xml")
    extract_items_from_xml(xml_file_path)
