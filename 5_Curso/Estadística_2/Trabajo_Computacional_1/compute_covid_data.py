import sys
import json
import csv
from datetime import datetime as dt
from datetime import timedelta

DATES_LIST_PER_MONTH = ["01/02/2020", "01/03/2020", "01/04/2020", "01/05/2020", "01/06/2020",\
                        "01/07/2020", "01/08/2020", "01/09/2020", "01/10/2020", "01/11/2020"]

DATES_LIST_PER_15DAYS = ["01/02/2020", "15/02/2020", "01/03/2020", "15/03/2020", "01/04/2020",\
                         "15/04/2020", "01/05/2020", "15/05/2020", "01/06/2020", "15/06/2020",\
                         "01/07/2020", "15/07/2020", "01/08/2020", "15/08/2020", "01/09/2020",\
                         "15/09/2020", "01/10/2020", "15/10/2020", "01/11/2020"]


def convert_to_date_obj(dates_str_list):
    dates_objs = []
    for date_item in dates_str_list:
        dates_objs.append(dt.strptime(date_item, '%d/%m/%Y'))
    return dates_objs



def get_countries(data_dict):
    countries = []

    for item in data_dict:
        if item['countriesAndTerritories'] not in countries:
            countries.append(item['countriesAndTerritories'])

    return countries



def get_posterior_date(current_date, dates_list):
    for date_item in dates_list:
        if current_date < date_item:
            return date_item
    return None



def compute_count(filename, dates_interval):
    with open(filename) as f:
        data = json.load(f)['records']

    dates_list = convert_to_date_obj(dates_interval)

    computed_dict = {}

    for item in data:
        dateRep = dt.strptime(item['dateRep'], '%d/%m/%Y')
        date_post = get_posterior_date(dateRep, dates_list)
        if date_post:
            if item['countriesAndTerritories'] in computed_dict:
                date_cases_update = False
                for list_item in computed_dict[item['countriesAndTerritories']]:
                    if list_item[0] == date_post:
                        list_item[1] += item['cases']
                        date_cases_update = True
                        break
                if date_cases_update == False:
                    computed_dict[item['countriesAndTerritories']].append([date_post, item['cases']])

            else:
                computed_dict[item['countriesAndTerritories']] = [[date_post, item['cases']]]

    return computed_dict


def computed_data_to_csv(computed_data, csv_file, dates_interval):

    f_out = open(csv_file, 'w')

    headers = "Countries"
    for it in dates_interval:
        headers += ';'+it
    headers += '\n'

    f_out.write(headers)

    for country in computed_data:
        line_list = [0]*len(dates_interval)
        line = country
        for data_item in computed_data[country]:
            for (date_idx, date_val) in enumerate(dates_interval):
                if date_val == data_item[0].strftime('%d/%m/%Y'):
                    line_list[date_idx] = data_item[1]

        for item in line_list:
            line += ';'+str(item)
        line += '\n'
        f_out.write(line)

    f_out.close()



def world_covid_per15days():
    computed_dict = compute_count('world_covid.json', DATES_LIST_PER_15DAYS)

    computed_data_to_csv(computed_dict, 'world_covid_per15days.csv', DATES_LIST_PER_15DAYS)



def world_covid_perDay(filename_in, filename_out):
    with open(filename_in) as f:
        data = json.load(f)['records']


    dates_list = []
    for item in data:
        if item['dateRep'] not in dates_list:
            dates_list.append(item['dateRep'])

    dates_list_obj = [dt.strptime(it,'%d/%m/%Y') for it in dates_list]
    dates_list_obj = sorted(dates_list_obj)
    dates_list_str = [it.strftime('%d/%m/%Y') for it in dates_list_obj]

    headers = 'Countries'
    for it in dates_list_str:
        headers += ';'+it
    headers += '\n'

    f_out = open(filename_out, 'w')
    f_out.write(headers)

    current_country = data[0]['countriesAndTerritories']
    line_list = [0]*len(dates_list_str)
    for item in data:
        if current_country != item['countriesAndTerritories']:
            new_line = current_country
            for it in line_list:
                new_line += ';'+str(it)
            f_out.write(new_line+'\n')
            current_country = item['countriesAndTerritories']
            line_list = [0]*len(dates_list_str)

        else:
            idx = dates_list_str.index(item['dateRep'])
            line_list[idx] = item['cases']

    f_out.close()



def create_dates_interval(ndays=7):
    base = dt.strptime('01/01/2020','%d/%m/%Y') # January 1st, 2020
    max_days = 316 # January 1st, 2020 + 515 days = Nov. 12, 2020

    if ndays > max_days:
        print("Error: ndays cannot be greater than 315 days")
        exit()

    return [(base + timedelta(days=n)).strftime('%d/%m/%Y') for n in range(0, max_days, ndays)]



def main():
    dates_interval = create_dates_interval(ndays=5)
    computed_dict = compute_count('world_covid.json', dates_interval)
    computed_data_to_csv(computed_dict, 'world_covid_per5days.csv', dates_interval)


if __name__ == "__main__":
    main()
