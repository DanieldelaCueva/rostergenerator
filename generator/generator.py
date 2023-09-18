import jinja2
import pdfkit

def generate_pdf(context, player_list, coach_list, equipo, output_directory):
    template_loader = jinja2.FileSystemLoader('./')
    template_env = jinja2.Environment(loader=template_loader)

    html_template = "/templates/roster_template.html"
    template = template_env.get_template(html_template)

    output_text = template.render(context)

    insert1_index = output_text.find("<!--insert1-->")+14

    add1 = ""

    for player in player_list:
        add1 += f"<tr style='height: 18px;'><td style='width: 10%; height: 18px; text-align: center;'>{player['num']}</td><td style='width: 45%; height: 18px;'>{player['surname']}</td><td style='width: 45%; height: 18px;'>{player['name']}</td></tr>"

    prov1_text = output_text[:insert1_index] + add1 + output_text[insert1_index:]

    insert2_index = prov1_text.find("<!--insert2-->")+14

    add2 = ""

    for coach in coach_list:
        add2 += f"<tr style='height: 18px;'><td style='width: 10%; height: 18px; text-align: center;'>{coach['num']}</td><td style='width: 45%; height: 18px;'>{coach['surname']}</td><td style='width: 45%; height: 18px;'>{coach['name']}</td></tr>"

    prov2_text = prov1_text[:insert2_index] + add2 + prov1_text[insert2_index:]

    config = pdfkit.configuration(wkhtmltopdf=r'C:\Program Files\wkhtmltopdf\bin\wkhtmltopdf.exe')
    output_pdf = fr"{output_directory}\roster-{equipo}-{context['game_date']}.pdf"
    pdfkit.from_string(prov2_text, output_pdf, configuration=config)