#include <iostream>
#include <string>
#include <limits> // Used for clearing input buffer

// Step 2: Define the Node Structure
struct Node {
    std::string description;
    int priority;
    Node* next;
};

// Step 3: Create the TodoList Class
class TodoList {
private:
    Node* head; // Pointer to the start of the list

public:
    // Constructor
    TodoList() {
        head = nullptr;
    }

    // Destructor (for memory cleanup)
    ~TodoList() {
        Node* current = head;
        Node* nextNode = nullptr;
        while (current != nullptr) {
            nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // Add a task in order of priority
    void addTask(std::string desc, int prio) {
        Node* newNode = new Node;
        newNode->description = desc;
        newNode->priority = prio;
        newNode->next = nullptr;

        if (head == nullptr || prio < head->priority) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* current = head;
        while (current->next != nullptr && current->next->priority <= prio) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    // Delete a task by its position in the list
    void deleteTask(int taskNumber) {
        if (head == nullptr) {
            std::cout << "The list is already empty.\n";
            return;
        }

        Node* temp = head;
        if (taskNumber == 1) {
            head = head->next;
            delete temp;
            std::cout << "Task 1 completed and removed.\n";
            return;
        }

        Node* prev = nullptr;
        for (int i = 1; i < taskNumber && temp != nullptr; i++) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            std::cout << "Invalid task number.\n";
            return;
        }

        prev->next = temp->next;
        delete temp;
        std::cout << "Task " << taskNumber << " completed and removed.\n";
    }

    // Display all tasks
    void displayTasks() {
        std::cout << "\n--- To-Do List ---\n";
        if (head == nullptr) {
            std::cout << "The list is empty. Great job!\n";
            std::cout << "--------------------\n";
            return;
        }

        Node* current = head;
        int taskNumber = 1;
        while (current != nullptr) {
            std::cout << taskNumber << ". " << current->description
                      << " (Priority: " << current->priority << ")\n";
            current = current->next;
            taskNumber++;
        }
        std::cout << "--------------------\n";
    }
};

// Step 5: The Main Function (User Interface)
void printMenu() {
    std::cout << "\n===== MENU =====\n";
    std::cout << "1. Add a new task\n";
    std::cout << "2. Complete a task\n";
    std::cout << "3. View all tasks (refreshes automatically)\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    TodoList myList;
    int choice = 0;
    std::string description;
    int priority;
    int taskNum;

    do {
        myList.displayTasks();
        printMenu();
        std::cin >> choice;

        // Handle non-integer input
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = -1; // Set to an invalid choice
        }

        switch (choice) {
            case 1:
                std::cout << "Enter task description: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, description);
                std::cout << "Enter priority (e.g., 1 for high, 5 for low): ";
                std::cin >> priority;
                myList.addTask(description, priority);
                break;
            case 2:
                std::cout << "Enter the task number to complete: ";
                std::cin >> taskNum;
                myList.deleteTask(taskNum);
                break;
            case 3:
                // List is already shown, so we just loop again
                break;
            case 4:
                std::cout << "Exiting program. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
