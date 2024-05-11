#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <exception>

using namespace std;


// define my custom exception
class MyException : public exception {
public:
    const char* what() const noexcept override {
        return "Value not in the required range!";
    }
};

class Resource{
protected:
    string resource_name;
    double quantity;
    double hourly_cost;
public:
    // constructor for Resource objects
    Resource(const string& resource_name_, double quantity_, double hourly_cost_):
        resource_name(resource_name_), quantity(quantity_),hourly_cost(hourly_cost_){}

    // default constructor
    Resource(){}

    // virtual destructor
    virtual ~Resource() {}

    // pure virtual function to calculate cost
    virtual double calculate_cost() const = 0;


    virtual ostream& print(ostream& os) const {
        os << "Resource Name: " << resource_name << endl;
        os << "Quantity: " << quantity << endl;
        os << "Hourly Cost: " << hourly_cost << endl;
        return os;
    }

    friend ostream& operator<<(ostream& os, const Resource& resource) {
        return resource.print(os);
    }

    virtual istream& read(istream& is) {
        cout << "Enter resource name: ";
        getline(is >> ws, resource_name);
        cout << "Enter resource quantity: ";
        is >> quantity;
        cout << "Enter resource hourly cost: ";
        is >> hourly_cost;
        return is;
    }

    friend istream& operator>>(istream& is, Resource& resource) {
        return resource.read(is);
    }


     // overload == operator for class Resource
    bool operator==(const Resource& other) const {
        return (resource_name == other.resource_name &&
                quantity == other.quantity &&
                hourly_cost == other.hourly_cost);
    }

    // getters and setters
    double get_resource_hourly_cost()
    const {
        return hourly_cost;
    }

    double get_quantity()
    const {
        return quantity;
    }
    void set_quantity(double quantity_)
    {
        quantity = quantity_;
    }
    string get_resource_name()
    const {
        return resource_name;
    }
    void set_resource_name(const string& name) {
    resource_name = name;
    }

    void set_resource_hourly_cost(double hourly_cost_) {
    hourly_cost = hourly_cost_;
    }


};

class LaborResource : public Resource {
    string role;
    int experience_years;
    int rating;
public:
    // Initialization Constructor
    LaborResource(string resource_name_, double quantity_, double hourly_cost_, string role_, int experience_years_, int rating_):
        Resource(resource_name_, quantity_, hourly_cost_), role(role_), experience_years(experience_years_), rating(rating_) {}


    // default constructor
    LaborResource(){}


    // calculate cost, override base class function
    double calculate_cost() const override {
        return quantity * hourly_cost * (rating / 10);
    }

    ostream& print(ostream& os) const override {
        Resource::print(os);
        os << "Labor Resource Role: " << get_role() << endl;
        os << "Experience Years: " << get_experience_years() << endl;
        os << "Rating: " << get_rating() << endl;
        return os;
    }

    friend ostream& operator<<(ostream& os, const LaborResource& laborresource)
    {
        return laborresource.print(os);
    }

    istream& read(istream& is) override {
        Resource::read(is); // Call base class read function
        cout << "Enter labor resource role: ";
        getline(is >> ws, role);
        cout << "Enter labor resource experience years: ";
        is >> experience_years;
        cout << "Enter labor rating: ";
        is >> rating;
        return is;
    }
    friend istream& operator>>(istream& is, LaborResource& laborresource)
    {
        return laborresource.read(is);
    }

    string get_role() const {
        return role;
    }

    void set_role(const string& role_) {
        role = role_;
    }

    int get_experience_years() const {
        return experience_years;
    }

    void set_experience_years(int years) {
        experience_years = years;
    }
    int get_rating() const{
        return rating;
    }
    void throwCustomException() const {
        throw MyException();
    }

    // Metodă pentru a arunca o excepție standard
    void throwStandardException() const {
        throw runtime_error("A standard exception occurred!");
    }
};

class SoftwareResource : public Resource {
    string type;
    string version;
    double reduction;
public:
    // Initialization Constructor
    SoftwareResource(const string& resource_name_, double quantity_, double hourly_cost_, const string& type_, const string& version_, double reduction_):
        Resource(resource_name_, quantity_, hourly_cost_), type(type_), version(version_), reduction(reduction_) {}

    // default constructor
    SoftwareResource(){}


    // calculate cost and override base class function
    double calculate_cost() const override {
        return quantity * hourly_cost * reduction;
    }


     ostream& print(ostream& os) const override {
        Resource::print(os); // Call base class print function
        os << "Software Resource Type: " << type << endl;
        os << "Version: " << version << endl;
        os << "Reduction: " << reduction << endl;
        return os;
        }

     friend ostream& operator<<(ostream& os, const SoftwareResource& softwareresource)
     {
         return softwareresource.print(os);
     }

    istream& read(istream& is) override {
        Resource::read(is); // Call base class read function
        cout << "Enter software resource type: ";
        getline(is >> ws, type);
        cout << "Enter software resource version: ";
        getline(is >> ws, version);
        cout << "Enter the reduction percentage: ";
        is >> reduction;
        return is;
        }

    friend istream& operator>>(istream& is, SoftwareResource& softwareresource)
    {
        return softwareresource.read(is);
    }

    string get_type() const {
        return type;
    }

    void set_type(const string& type_) {
        type = type_;
    }

    string get_version() const {
        return version;
    }

    void set_version(const string& version_) {
        version = version_;
    }
    double get_reduction() const {
        return reduction;
    }
};

class Task{

protected:
    string task_name;
    int priority; // range 1-3 1=low, 2=medium, 3=high
    string task_status; //in-progress, completed,delayed
    int start_date;
    int end_date;
    vector<LaborResource> labor_resources;
    vector<SoftwareResource> software_resources;
public:
    // constructor for Task objects
    Task(const string& task_name_, int priority_, const string& task_status_, int start_date_, int end_date_, const vector<LaborResource>& labor_resources_, const vector<SoftwareResource>& software_resource_):
        task_name(task_name_), priority(priority_), task_status(task_status_), start_date(start_date_), end_date(end_date_), labor_resources(labor_resources_), software_resources(software_resource_){}

    // default constructor
    Task() = default;

    // virtual destructor
    virtual ~Task() {}

    // pure virtual function for calculate cost for a task
    virtual double calculate_task_cost() const = 0;


    // methods
    double calculate_total_cost() const {
        double total_cost = 0.0;

        // Calculate cost for labor resources
        for (const auto& labor_res : labor_resources) {
            total_cost += labor_res.calculate_cost();     // dynamic dispatch
        }

        // Calculate cost for software resources
        for (const auto& software_res : software_resources) {
            total_cost += software_res.calculate_cost();    // dynamic dispatch
        }

        return total_cost;
    }


     virtual ostream& print(ostream& os) const {
        os << "Task Name: " << task_name << endl;
        os << "Priority: " << priority << endl;
        os << "Task Status: " << task_status << endl;
        os << "Start Date: " << start_date << endl;
        os << "End Date: " << end_date << endl;

        os << "Labor Resources:" << endl;
        for (const auto& labor_res : labor_resources) {
            os << labor_res;
        }

        os << "Software Resources:" << endl;
        for (const auto& software_res : software_resources) {
            os << software_res;
        }

        return os;
    }

    // Virtual function for reading the task details
    virtual istream& read(istream& is) {
        cout << "Enter Task Name: ";
        getline(is >> ws, task_name);
        cout << "Enter Priority (1-3): ";
        is >> priority;
        cout << "Enter Task Status: ";
        getline(is >> ws, task_status);
        cout << "Enter Start Date: ";
        is >> start_date;
        cout << "Enter End Date: ";
        is >> end_date;

        // Read labor resources
        cout << "Enter Labor Resources:" << endl;
        LaborResource labor_res;
        while (is >> labor_res) {
            labor_resources.push_back(labor_res);
        }
        is.clear(); // Clear stream state after reading labor resources

        // Read software resources
        cout << "Enter Software Resources:" << endl;
        SoftwareResource software_res;
        while (is >> software_res) {
            software_resources.push_back(software_res);
        }
        is.clear(); // Clear stream state after reading software resources

        return is;
    }

    friend ostream& operator<<(ostream& os, const Task& task) {
        return task.print(os);
    }

    friend istream& operator>>(istream& is, Task& task) {
        return task.read(is);
    }


    // getters and setters
    vector<LaborResource> get_LaborResource() const {
        return labor_resources;
    }
    vector<SoftwareResource> get_SoftwareResource() const {
        return software_resources;
    }
    int get_start_date() const {
        return start_date;

    }
    int get_end_date() const {
        return end_date;
    }



};



class BugTask : public Task {
    string bug_description;
    int severity; // Number between 1 and 3

public:
    // Initialization Constructor
    BugTask(const string& task_name_, int priority_, const string& task_status_, int start_date_, int end_date_,
            const string& bug_description_, int severity_,
            const vector<LaborResource>& labor_resources_, const vector<SoftwareResource>& software_resources_) :
        Task(task_name_, priority_, task_status_, start_date_, end_date_, labor_resources_, software_resources_),
        bug_description(bug_description_), severity(severity_) {}

    // Default constructor
    BugTask() : bug_description(""), severity(0){}


    // methods
   virtual double calculate_task_cost() const override {
        double cost = Task::calculate_total_cost();
        double multiplier = 1.0;
        if (severity == 2) {
            multiplier = 1.1;
        } else if (severity == 3) {
            multiplier = 1.2;
        }
        if(severity < 1 || severity > 3)
        {
            throw MyException();
        }
        return cost * multiplier;
    }


    ostream& print(ostream& os) const override {
        Task::print(os); // Call base class print function
        os << "Bug Description: " << bug_description << endl;
        os << "Severity: " << severity << endl;
        return os;
    }

    // Override read function
    istream& read(istream& is) override {
        Task::read(is); // Call base class read function
        cout << "Enter Bug Description: ";
        getline(is >> ws, bug_description);
        cout << "Enter Severity (1-3): ";
        is >> severity;
        return is;
    }
    friend ostream& operator<<(ostream& os, const BugTask& task) {
        return task.print(os);
    }

    friend istream& operator>>(istream& is, BugTask& task) {
        return task.read(is);
    }




    //getters and setters
    string getBugDescription() const {
        return bug_description;
    }

    int getSeverity() const {
        return severity;
    }
};





class FeatureTask : public Task {
private:
    string feature_description;
    int complexity; // 1 - low, 2 - medium, 3 - high

public:
    // Initialization Constructor
    FeatureTask(const string& task_name_, int priority_, const string& task_status_, int start_date_, int end_date_,
                const string& feature_description_, const string& customer_feedback_, int complexity_,
                const vector<LaborResource>& labor_resources_, const vector<SoftwareResource>& software_resources_) :
        Task(task_name_, priority_, task_status_, start_date_, end_date_, labor_resources_, software_resources_),
        feature_description(feature_description_), complexity(complexity_) {}

    // Override calculate_task_cost for dynamic dispatch
   virtual double calculate_task_cost() const override {
        double base_cost = Task::calculate_total_cost();
        double additional_cost = 0.0;
        if(getComplexity() < 1 || getComplexity() > 3)
        {
            throw MyException();
        }
        else
        {
             additional_cost = getComplexity() * 100;
            return base_cost + additional_cost;
        }
    }

    ostream& print(ostream& os) const override {
        Task::print(os); // Call base class print function
        os << "Feature Description: " << feature_description << endl;
        os << "Complexity: " << complexity << endl;
        return os;
    }

    // Override read function
    istream& read(istream& is) override {
        Task::read(is); // Call base class read function
        cout << "Enter Feature Description: ";
        getline(is >> ws, feature_description);
        cout << "Enter Complexity (1-3): ";
        is >> complexity;
        return is;
    }

    friend ostream& operator<<(ostream& os, const FeatureTask& task) {
        return task.print(os);
    }

    friend istream& operator>>(istream& is, FeatureTask& task) {
        return task.read(is);
    }


    // Getters for feature description, customer feedback, and complexity
    string getFeatureDescription() const {
        return feature_description;
    }


    int getComplexity() const {
        return complexity;
    }
};



class ResearchTask : public Task{
private:
    string topic;
public:

    // Initialization Constructor
    ResearchTask(const string& task_name_, int priority_, const string& task_status_, int start_date_, int end_date_,
                 const string& topic_,
                 const vector<LaborResource>& labor_resources_, const vector<SoftwareResource>& software_resources_) :
        Task(task_name_, priority_, task_status_, start_date_, end_date_, labor_resources_, software_resources_),
        topic(topic_) {}

    // Default Constructor
    ResearchTask() : Task(), topic("") {}

    // Override calculate_task_cost for dynamic dispatch
    virtual double calculate_task_cost() const override {
        double base_cost = Task::calculate_total_cost();
        int research_time = get_end_date() - get_start_date();
        double additional_daily_cost = 50;
        return base_cost + (research_time * 50);
    }


     ostream& print(ostream& os) const override {
        Task::print(os); // Call base class print function
        os << "Research Topic: " << topic << endl;
        return os;
    }

    // Override read function
    istream& read(istream& is) override {
        Task::read(is); // Call base class read function
        cout << "Enter Research Topic: ";
        getline(is >> ws, topic);
        return is;
    }
    friend ostream& operator<<(ostream& os, const ResearchTask& task) {
        return task.print(os);
    }

    friend istream& operator>>(istream& is, ResearchTask& task) {
        return task.read(is);
    }


    // getters and setters
    string get_topic() const {
        return topic;

    }
};



class Project{
private:
    static int projectCount; // static member variable

    string project_name;
    int start_date_p;
    int end_date_p;
    string project_status;
    double estimated_revenue;
    vector<LaborResource> labor_resources;
    vector<SoftwareResource> software_resources;
    vector<BugTask> bug_task_list;
    vector<FeatureTask> feature_task_list;
    vector<ResearchTask> research_task_list;
public:
    // Constructor with initialization list
    Project(const string& project_name_, int start_date_, int end_date_, const string& project_status_, const double& estimated_revenue_,
            const vector<LaborResource>& labor_resources_, const vector<SoftwareResource>& software_resources_,
            const vector<BugTask>& bug_task_list_, const vector<FeatureTask>& feature_task_list_,
            const vector<ResearchTask>& research_task_list_) :
         project_name(project_name_), start_date_p(start_date_), end_date_p(end_date_), project_status(project_status_),
         estimated_revenue(estimated_revenue_), labor_resources(labor_resources_), software_resources(software_resources_),
         bug_task_list(bug_task_list_), feature_task_list(feature_task_list_), research_task_list(research_task_list_) {projectCount++;}

    // Copy constructor
    Project(const Project& other) :
        project_name(other.project_name), start_date_p(other.start_date_p), end_date_p(other.end_date_p),
        project_status(other.project_status), estimated_revenue(other.estimated_revenue),
        labor_resources(other.labor_resources), software_resources(other.software_resources),
        bug_task_list(other.bug_task_list), feature_task_list(other.feature_task_list),
        research_task_list(other.research_task_list) {}

    // Default constructor
    Project() {}

    // static methods which makes use of projectCount static variable
    static int getProjectCount() {
        return projectCount;
    }

    static void resetProjectCount() {
        projectCount = 0;
    }
    static void displayProjectCount() {
        cout << "Total projects created: " << projectCount << endl;
    }

};

int Project::projectCount = 0;

int main() {

    // we build the data we will test our functionalities on
    LaborResource labor1("John Bill", 1, 50.0, "Developer", 5, 8);
    LaborResource labor2("Jane Smith", 1, 45.0, "Tester", 3, 7);

    SoftwareResource software1("Software 1", 1, 100.0, "Type 1", "Version 1.0", 0.9);
    SoftwareResource software2("Software 2", 1, 150.0, "Type 2", "Version 2.0", 0.85);

    vector<BugTask> bugTasks;
    BugTask bugTask1("Bug Task 1", 3, "in-progress", 20240501, 20240515, "Description 1", 3, {labor1}, {software1});
    BugTask bugTask2("Bug Task 2", 2, "completed", 20240510, 20240520, "Description 2", 2, {labor2}, {software2});
    bugTasks.push_back(bugTask1);
    bugTasks.push_back(bugTask2);

    vector<FeatureTask> featureTasks;
    FeatureTask featureTask1("Feature Task 1", 2, "delayed", 20240505, 20240525, "Description 1", "Feedback 1", 3, {labor1}, {software1});
    FeatureTask featureTask2("Feature Task 2", 1, "in-progress", 20240515, 20240610, "Description 2", "Feedback 2", 1, {labor2}, {software2});
    featureTasks.push_back(featureTask1);
    featureTasks.push_back(featureTask2);

    vector<ResearchTask> researchTasks;
    ResearchTask researchTask1("Research Task 1", 1, "completed", 20240501, 20240510, "Topic 1", {labor1}, {software1});
    ResearchTask researchTask2("Research Task 2", 3, "in-progress", 20240515, 20240525, "Topic 2", {labor2}, {software2});
    researchTasks.push_back(researchTask1);
    researchTasks.push_back(researchTask2);

    Project project("Project 1", 20240501, 20240630, "in-progress", 5000.0, {labor1, labor2}, {software1, software2}, bugTasks, featureTasks, researchTasks);


    int choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. Calculate total cost for all tasks" << endl;
        cout << "2. Display all tasks" << endl;
        cout << "3. Handle exception for Feature Task with invalid complexity" << endl;
        cout << "4. Display the number of created projects using static variable" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Calculate total cost for all tasks
                double total_cost = 0;
                for (auto& bugtask : bugTasks) {
                    total_cost += bugtask.calculate_task_cost();
                }
                for (auto& featuretask : featureTasks) {
                    total_cost += featuretask.calculate_task_cost();
                }
                for (auto& researchtask : researchTasks) {
                    total_cost += researchtask.calculate_task_cost();
                }
                cout << "The total cost for the given project is: " << total_cost << endl;
                break;
            }
            case 2 : {

                    // upcasting
                    vector<Task*> allTasks;  // we create a vector of pointers to base class Task
                    for(auto& bugtask : bugTasks)
                    {
                        allTasks.push_back(&bugtask);   // instance of upcasting
                    }
                    for(auto& featuretask : featureTasks)
                    {
                        allTasks.push_back(&featuretask);   // instance of upcasting
                    }
                    for(auto& researchtask : researchTasks)
                    {
                        allTasks.push_back(&researchtask);   // instance of upcasting
                    }
                    for(auto& task : allTasks)     // instance of dynamic dispatch
                    {
                        cout << *task;
                    }
                    break;
            }
            case 3: {
                // Handle exception for Feature Task with invalid complexity
                FeatureTask featureTask3("Feature Task 3", 1, "in-progress", 20240515, 20240610, "Description 3", "Feedback 3", 6, {}, {});
                try {
                    double cost = featureTask3.calculate_task_cost();
                    cout << "Task cost: " << cost << endl;
                } catch (const MyException& e) {
                    cout << "Caught MyException: " << e.what() << endl;
                }
                break;
            }
            case 4: {

                 Project::displayProjectCount();  // test the static method which uses static variable

            }
            case 5: {
                cout << "Exiting program." << endl;
                break;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    } while (choice != 5);

    return 0;

    // we could use diamond inheritance in the following way:
    // SoftwareResource and LaborResource classes inherit virtually from Resource class like we did previously
    // A new class EmployeeResource inherits from both SoftwareResource and LaborResource
}
