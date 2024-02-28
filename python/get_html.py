import xml.etree.ElementTree as ET
from pathlib import Path
from web_pages import projects
from bs4 import BeautifulSoup
import os

def process_html(html_in, filename):
    html_in = "".join([s for s in html_in.strip().splitlines(True) if s.strip()])

    soup = BeautifulSoup(html_in, 'html.parser')
    html_elements = soup.find_all(['div', 'hr', 'pre', 'a'], recursive=False)
    #if filename == "procharge-support":
        #print(html_elements)

    all_classes = set()
    html_out = ""

    for index, html in enumerate(html_elements, start=1):

        if html.name == "hr":
            html_out = html_out + f'<hr>\n\n'
        if html.name == "a":
            name = html.get('name', [])
            if len(name) > 0:
                html_out = html_out + f'<a name="{name}"></a>\n'
        else:
            div_class = html.get('class', [])
            if len(div_class) > 0:
                div_class = div_class[0]
                all_classes.update([div_class])

                if div_class == "source-code":
                    #print(f"found source code {html.text}")
                    html_out = html_out + '<div class="code_block">\n'
                    html_out = html_out + ' <p>\n'
                    html_out = html_out + '   ' + html.text.replace('\n', '<br>') + '<br>\n'
                    html_out = html_out + ' </p>\n'
                    html_out = html_out + '</div>\n\n'

                elif div_class == "sqs-gallery-container" or div_class == "image-block-outer-wrapper":
                    # Find all <img> tags within the current div
                    images = html.find_all('img')
                    unique_images = set()



                    for image in images:
                        image = image['src'].rsplit('/', 1)[-1]
                        image = "{{ site.url }}/images/portfolio/" + filename + "/" + image
                        unique_images.update([image])

                    if div_class == "sqs-gallery-container":
                        html_out = html_out + '<ul class="projects clearfix">\n'
                        for image in unique_images:
                            html_out = html_out + '  <li>\n'
                            html_out = html_out + '    <div class="project" style=\'background-image: url(' + image + ')\'>\n'
                            html_out = html_out + '      <a class="cover" href="' + image + '"></a>\n'
                            html_out = html_out + '    </div>\n'
                            html_out = html_out + '  </li>\n'
                        html_out = html_out + '</ul>\n'
                        html_out = html_out + '<br>\n'
                    elif div_class == "image-block-outer-wrapper":
                        links = html.find_all('a')
                        if len(links) > 0:
                            href = links[0].get('href', [])
                            #print(f"Found images with links: {href}")
                        else:
                            href = image
                        html_out = html_out + f'<div class="projects clearfix">\n'
                        html_out = html_out + f' <a href="{href}">\n'
                        if "Sponsored+by+PCBWay" in image:
                            print("Found sponsored by PCBWay")
                            html_out = html_out + f'  <img class = "pcbway" src = "{image}">\n'
                        else:
                            html_out = html_out + f'  <img src = "{image}">\n'
                        html_out = html_out + f' </a>\n'
                        html_out = html_out + f'</div>\n'
                    html_out = html_out + "<br>\n\n"

                elif div_class == "sqs-html-content":
                    html_out = html_out + html.prettify()
                    html_out = html_out + "\n\n"
                    pass

                elif div_class == "sqs-block-button-container":

                    link = html.find_all('a')
                    href = link[0].get('href', [])
                    text = link[0].text

                    html_out = html_out + '<div class="projects clearfix">\n'
                    html_out = html_out + f' <a href="{href}">\n'
                    html_out = html_out + '  <button class="button" role="button">'
                    html_out = html_out + f'   {text}'
                    html_out = html_out + '  </button>\n'
                    html_out = html_out + ' </a>\n'
                    html_out = html_out + '</div>\n'
                    html_out = html_out + '<br>\n'
                    html_out = html_out + "\n\n"

                elif div_class == "intrinsic":
                    div = html.find_all('div', recursive=True)
                    html_out = html_out + '<div class="projects clearfix">\n'
                    html_out = html_out + div[1].get('data-html', []) + "\n"
                    html_out = html_out + '<br>\n'
                    html_out = html_out + "\n\n"

    #html_out = html_in

    if 'href="/s' in html_out:
        #print(f"detected file download in {filename}")
        html_out = html_out.replace('href="/s', 'href="{{ site.url }}/files/'+filename)
        output_dir = Path("C:/Users/10sta/GoogleDrive/Four Boards/Website New/fourboards/files/" + filename)
        try:
            os.mkdir(output_dir)
        except FileExistsError:
            pass

    if 'href="/' in html_out:
        #print(f"detected local page link in {filename}")
        html_out = html_out.replace('href="/', 'href="{{ site.url }}/')

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

                #print(f"processing {link}")
                content = process_html(content_encoded, link)

                extension = "md"
                if projects[link] == "other":
                    extension = "html"

                # Create an HTML file with the link name
                html_filename = f"C:/Users/10sta/GoogleDrive/Four Boards/Website New/fourboards/_{projects[link]}/{link}.{extension}"

                with open(html_filename, 'w', encoding='utf-8') as html_file:
                    # Write HTML content to the file

                    html_file.write("---\n")
                    html_file.write("layout: post\n")
                    html_file.write(f"uid: {link}\n")
                    html_file.write(f"title:  '{title}'\n")
                    if (link == "touchpad") or (link == "procharge"):
                        html_file.write(f"tags: portfolio\n")
                    else:
                        html_file.write(f"tags: portfolio arrows\n")
                    html_file.write("---\n")
                    html_file.write("\n")
                    html_file.write(f"{content}")
            else:
                #print(f"Skipped (not in list) {link}")
                pass
        else:
            #print(f"Skipped (element is none) {link_element}")
            pass


if __name__ == "__main__":
    xml_file_path = Path("export.xml")
    extract_items_from_xml(xml_file_path)
