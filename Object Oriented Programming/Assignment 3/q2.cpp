#include <iostream>
using namespace std;

class Question
{
protected:
    string questionText;
    int marks;

public:
    Question(string text, int mrks) : questionText{text}, marks{mrks} {}

    virtual void print() const
    {
        cout << "Question [" << marks << " marks]: " << questionText << "\n";
    }

    virtual ~Question() = default;
};

class EssayQuestion : public Question
{
private:
    int wordLimit;

public:
    EssayQuestion(string text, int mrks, int limit) : Question{text, mrks}, wordLimit{limit} {}

    void print() const override
    {
        Question::print();
        cout << "Word Limit: " << wordLimit << "\n";
    }
};

class MCQQuestion : public Question
{
private:
    string *options;
    int optionsCount;
    string correctOption;

public:
    MCQQuestion(string text, int mrks, string *opts, int optionsCnt, string crctOptn) : Question{text, mrks}, options{nullptr}, optionsCount{optionsCnt}, correctOption{crctOptn}
    {
        if (!opts)
            throw "Opts can't be a nullptr\n";

        options = new string[optionsCount];
        for (int i = 0; i < optionsCount; ++i)
        {
            options[i] = opts[i];
        }
    }

    void print() const override
    {
        Question::print();
        for (int i = 0; i < optionsCount; ++i)
        {
            cout << (i + 1) << ". " << options[i] << "\n";
        }
        cout << "(Correct Option: " << correctOption << ")\n";
    }

    ~MCQQuestion()
    {
        if (options)
            delete[] options;
    }
};

class QuestionPaper
{
private:
    Question *questions[10];
    int count = 0;

public:
    void addQuestion(Question *q)
    {
        questions[count] = q;
        count++;
    }

    void showAllQuestions() const
    {
        for (int i = 0; i < count; ++i)
        {
            questions[i]->print();
        }
    }

    ~QuestionPaper()
    {
        if (questions)
        {
            for (int i = 0; i < count; ++i)
            {
                delete questions[i];
            }
        }
    }
};

int main()
{
    QuestionPaper paper;
    Question *q1 = new EssayQuestion("Explain the concept of inheritance in OOP.", 10, 300);
    paper.addQuestion(q1);
    string optionsForQ2[4] = {"Inheritance", "Encapsulation", "Virtual Functions",
                              "Abstraction"};
    Question *q2 = new MCQQuestion("Which of the following is a polymorphic feature in OOP?",
                                   5, optionsForQ2, 4, "Virtual Functions");
    paper.addQuestion(q2);
    paper.showAllQuestions();
    return 0;
}