#include <iostream>
#include <string>
using namespace std;

/* takeaways
   - two pointers to track the traverse 
     of each poly linked list
   - the pointer for for the poly with
     more higher degree terms will advance
     faste
   - Don't forget to copy the leftover terms
     - in most cases you will have leftover
       due to how the two poniters move
     - example that will not have letfover
       poly1: 5x^3 + 4x^2 + 1
       poly2: 4x^3 + 5x^2 + 1
*/
struct Node
{
  Node *next;
  int coeff;
  int pow;
};

void push(Node **head, int coeff, int pow)
{
  Node *newNode = new Node;
  newNode->next = *head;
  newNode->coeff = coeff;
  newNode->pow = pow;
  /* the node pushed is the new head */
  *head = newNode;
}

Node *newNode(int coeff, int pow)
{

  Node *newNode = new Node;
  newNode->next = nullptr;
  newNode->coeff = coeff;
  newNode->pow = pow;
  return newNode;
}

string showPolys(Node *head)
{
  if (head == nullptr)
    return "[]";
  string result = "[";
  while (head != nullptr)
  {
    result = result + "[" + std::to_string(head->coeff) + "," +
             std::to_string(head->pow) + "]";

    if (head->next != nullptr)
      result += ",";
    head = head->next;
  }
  result += "]";
  return result;
}

class Solution
{
public:
  Node *addPolys(Node *poly1, Node *poly2)
  {
    Node *poly = nullptr;
    /* point to the resulting poly */
    Node *head = nullptr;
    /* both polys have terms */
    while (poly1 != nullptr && poly2 != nullptr)
    {
      // pow doesn't matter;
      Node *temp = newNode(0, 0);
      if (poly1->pow == poly2->pow)
      {
        // randomly pick one
        temp->pow = poly1->pow;
        temp->coeff = poly1->coeff + poly2->coeff;
        //both move to the next term
        poly1 = poly1->next;
        poly2 = poly2->next;
      }
      /* 
         - take the term that has a higher degree
         - move its pointer to the next   
      */
      else
      {
        if (poly1->pow > poly2->pow)
        {
          temp->pow = poly1->pow;
          temp->coeff = poly1->coeff;
          poly1 = poly1->next;
        }
        else if (poly2->pow > poly1->pow)
        {
          temp->pow = poly2->pow;
          temp->coeff = poly2->coeff;
          poly2 = poly2->next;
        }
      }

      if (temp->coeff != 0)
      {
        if (poly == nullptr)
        {
          head = temp;
          poly = head;
        }
        else
        {
          poly->next = temp;
          poly = poly->next;
        }
      }
    }
    /* 
       - copy the leftover terms from either poly1 or poly2
         has lefover terms bot not both 
    */

    while (poly1 != nullptr || poly2 != nullptr)
    {
      Node *temp = newNode(0, 0);
      if (poly1 != nullptr)
      {
        temp->coeff = poly1->coeff;
        temp->pow = poly1->pow;
        poly1 = poly1->next;
      }
      else
      {
        temp->coeff = poly2->coeff;
        temp->pow = poly2->pow;
        poly2 = poly2->next;
      }
      poly->next = temp;
      poly = poly->next;
    }

    return head;
  }
};
// poly1 = [[1,1]], poly2 = [[1,0]]
void testFixture1(Node **poly1, Node **poly2)
{
  push(poly1, 1, 1);
  push(poly2, 1, 0);
}

// poly1 = [[2,2],[4,1],[3,0]], poly2 = [[3,2],[-4,1],[-1,0]]
void testFixture2(Node **poly1, Node **poly2)
{
  push(poly1, 3, 0);
  push(poly1, 4, 1);
  push(poly1, 2, 2);

  push(poly2, -1, 0);
  push(poly2, -4, 1);
  push(poly2, 3, 2);
}
// poly1 = [[1,2]], poly2 = [[-1,2]]
void testFixture3(Node **poly1, Node **poly2)
{
  push(poly1, 1, 2);
  push(poly2, -1, 2);
}

void test1()
{
  Node *p1 = nullptr;
  Node *p2 = nullptr;
  Node *p = nullptr;
  testFixture1(&p1, &p2);
  Solution sol;
  p = sol.addPolys(p1, p2);
  cout << "Test 1 - expect to see [[1,1],[1,0]]" << endl;

  cout << "result:"
       << showPolys(p);
}
void test2()
{
  Node *p1 = nullptr;
  Node *p2 = nullptr;
  Node *p = nullptr;
  testFixture2(&p1, &p2);
  Solution sol;
  p = sol.addPolys(p1, p2);
  cout << "Test 2 - expect to see [[5,2],[2,0]]" << endl;

  cout << "result:"
       << showPolys(p);
}
void test3()
{
  Node *p1 = nullptr;
  Node *p2 = nullptr;
  Node *p = nullptr;
  testFixture3(&p1, &p2);
  Solution sol;
  p = sol.addPolys(p1, p2);
  cout << "Test 3 - expect to see []" << endl;

  cout << "result:"
       << showPolys(p);
}

main()
{
  test1();
  cout << endl;
  test2();
  cout << endl;
  test3();
  cout << endl;
  return 0;
}
