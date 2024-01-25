from flask import Blueprint, render_template, request, redirect, url_for
from model import get_employees,get_employee, update_employee, add_employee , delete_employee, search_employee_name, search_employee_job, get_employee_info, get_persons

index = Blueprint('index', __name__)

@index.route('/') #this is the main page
def home():
    data = get_employees() #this is the data that will be passed to the template
    return render_template('main.html', items=data)

@index.route('/hire') #this is the hire page
def hire():
    item = get_persons() #this is the data that will be passed to the template
    return render_template('hire.html',items=item)

@index.route('/update/<id>', methods=['GET', 'POST']) # this is the update page
def update(id):
    if request.method == 'GET': # if the request is GET, then we will get the data from the database and pass it to the template
        item = get_employee(id)
        return render_template('update.html', item=item)
    else:
        item = get_employee(id)
        return render_template('update.html', item=item)

@index.route('/update/<id>/<firstname>&<middlename>&<lastname>&<jobtitle>', methods=['GET','POST']) # this is the flip side of the update page
def update_completed(id,firstname,middlename,lastname,jobtitle):
    jobtitle = jobtitle.replace("_", " ") # we convert jobtitle to the original format
    if request.method == 'GET':
        update_employee(id, firstname, middlename, lastname, jobtitle) # we update the database
        return redirect(url_for('index.home')) # we redirect to the main page
    else:
        return redirect(url_for('index.home'))
    
@index.route('/fire/<id>', methods=['GET', 'POST']) # this is the fire page
def fire(id):
    if request.method == 'GET':
        delete_employee(id) # we delete the employee from the database
        return redirect(url_for('index.home')) # we redirect to the main page
    else:
        return redirect(url_for('index.home'))
    
@index.route('/hire/<id>&<nationalidnumber>&<jobtitle>&<birthdate>&<maritalstatus>&<gender>&<hiredate>', methods=['GET','POST']) # this is the flip side of the hire page
def hire_completed(id,nationalidnumber,jobtitle,birthdate,maritalstatus,gender,hiredate):
    jobtitle = jobtitle.replace("_", " ") # we convert jobtitle to the original format
    if request.method == 'GET':
        add_employee(id,nationalidnumber,jobtitle,birthdate,maritalstatus,gender,hiredate) # we add the employee to the database
        return redirect(url_for('index.home')) # we redirect to the main page
    else:
        return redirect(url_for('index.home'))
    
@index.route('/action_page') # this is the search page
def search():
    search_type = request.args.get('search_type') # we get the search type
    search = request.args.get('search') # we get the search query
    if search == '': # if the search query is empty, we redirect to the main page
        return redirect(url_for('index.home')) 
    if search_type == 'fullname': # if the search type is fullname, we search by fullname
        data = search_employee_name(search)
    elif search_type == 'jobtitle': # if the search type is jobtitle, we search by jobtitle
        data = search_employee_job(search) 
    else:
        data = [] # if the search type is not fullname or jobtitle, we return an empty list
    return render_template('main.html', items=data) # we pass the data to the template

@index.route('/employee_info/<id>') # this is the employee info page
def employee_info(id): 
    item = get_employee_info(id) # we get the detailed employee info from the database
    return render_template('employee_info.html', items=item)