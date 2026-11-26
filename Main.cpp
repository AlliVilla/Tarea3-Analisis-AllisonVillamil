#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>

#define N1 1000
#define N2 10000
#define N3 100000
#define N4 1000000
#define N5 3000000

void swap(int &A, int &B) {
    int temp = A;
    A = B;
    B = temp; 
}

void mostrarBarra(int actual, int total) {
    int anchoBarra = 40;
    float progreso = (float)actual / total;
    int pos = anchoBarra * progreso;

    std::cout << "\rOrdenando: [";
    for (int i = 0; i < anchoBarra; ++i) {
        if (i < pos) std::cout << "█";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progreso * 100.0) << "% " << std::flush;
}

//---------------------------------------------------------------------------
void Selection_Sort(int arr[], int n) {
    int paso = n / 100; 
    if (paso == 0) paso = 1;

    for (int i = 0; i < n - 1; i++) {
        int min = i;
        
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        if (min != i) {
            swap(arr[i], arr[min]);
        }

        if (i % paso == 0 || i == n - 2) {
            mostrarBarra(i + 2, n);
        }
    }
    std::cout << '\n';
}
//---------------------------------------------------------------------------

void bubbleSort(int arr[], int n) {
    int paso = n / 100; 
    if (paso == 0) paso = 1;

    for (int i = 0; i < n - 1; i++) {
        bool intercambiado = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                intercambiado = true;
            }
        }
        if (i % paso == 0 || i == n - 2) {
            mostrarBarra(i + 2, n);
        }
        if (!intercambiado) {
            mostrarBarra(n, n);
            break;
        }
    }
    std::cout << '\n';
}
//---------------------------------------------------------------------------

void merge(int arr[], int izq, int medio, int der) {
    std::vector<int> aux;
    int i = izq;       
    int j = medio + 1; 

    while (i <= medio && j <= der) {
        if (arr[i] <= arr[j]) {
            aux.push_back(arr[i++]);
        } else {
            aux.push_back(arr[j++]);
        }
    }

    while (i <= medio) aux.push_back(arr[i++]);

    while (j <= der) aux.push_back(arr[j++]);

    for (int k = 0; k < aux.size(); k++) {
        arr[izq + k] = aux[k];
    }
}


void mergeSortRec(int arr[], int izq, int der) {
    if (izq >= der) return; 

    int medio = izq + (der - izq) / 2;

    mergeSortRec(arr, izq, medio);      
    mergeSortRec(arr, medio + 1, der);  
    merge(arr, izq, medio, der);     
}

void mergeSort(int arr[], int n) {
    if (n > 1) {
        mergeSortRec(arr, 0, n - 1);
    }
}

//---------------------------------------------------------------------------

int particion(int arr[], int izq, int der) {
    int pivote = arr[der]; 
    int i = izq - 1;       

    for (int j = izq; j < der; j++) {
        if (arr[j] < pivote) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[der]);
    return i + 1; 
}


void quickSortRec(int arr[], int izq, int der) {
    if (izq >= der) return; 

    int indicePivote = particion(arr, izq, der);

    quickSortRec(arr, izq, indicePivote - 1); 
    quickSortRec(arr, indicePivote + 1, der);
}

void quickSort(int arr[], int n) {
    if (n > 1) {
        quickSortRec(arr, 0, n - 1);
    }
}
//---------------------------------------------------------------------------

void heapify(int arr[], int n, int i) {
    int mayor = i;          
    int izq = 2 * i + 1;    
    int der = 2 * i + 2;    

    
    if (izq < n && arr[izq] > arr[mayor]) {
        mayor = izq;
    }

    
    if (der < n && arr[der] > arr[mayor]) {
        mayor = der;
    }

    
    if (mayor != i) {
        swap(arr[i], arr[mayor]);
        heapify(arr, n, mayor);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]); 
        heapify(arr, i, 0);   
    }
}

//---------------------------------------------------------------------------

void insertionSort(int arr[], int n) {
    int paso = n / 100; 
    if (paso == 0) paso = 1;
    for (int i = 1; i < n; i++) {
        int actual = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > actual) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = actual;

          if (i % paso == 0 || i == n - 2) {
            mostrarBarra(i + 2, n);
        }
    }
}

//---------------------------------------------------------------------------

int main() {
    int tamano = N3;
    
    
    int* arr = new int[tamano];

    srand(time(0));
    for (int i = 0; i < tamano; i++) {
        arr[i] = rand() % 1000000;
    }
    int opcion;
    std::string nombrealg;
    std::cout<<"=========SORTS============\n";
    std::cout<<"1. Selection sort.\n 2. Bubble Sort.\n 3. Merge Sort.\n 4. Quicksort. \n 5. Heap Sort.\n 6. Insertion Sort\n";
    std::cout<<"Elige una opcion:\n";
    std::cin>>opcion;
    clock_t inicio = clock();
    switch (opcion) {
        case 1:
        Selection_Sort(arr, tamano);
        nombrealg="Selection Sort";
        break;
        case 2:
        bubbleSort(arr, tamano); 
        nombrealg="Bubble Sort";
        break;
        case 3:
        mergeSort(arr, tamano);
        nombrealg="Merge Sort";
        break;
        case 4:
        quickSort(arr, tamano);
        nombrealg="Quick Sort";
        break;
        case 5:
        heapSort(arr, tamano); 
        nombrealg="Heap Sort";
        break;
        case 6:
        insertionSort(arr, tamano); 
        nombrealg="Insertion Sort";
        break;
        default:
        std::cout<<"Opcion no disponible \n";
        return 0;
    
    }
    
    
    clock_t fin = clock();

    double tiempo_segundos = double(fin - inicio) / CLOCKS_PER_SEC;
    std::cout<< "Algoritmo: "<<nombrealg<<'\n';
    std::cout << "Arreglo de " << tamano << " elementos ordenado." << '\n';
    std::cout << "Tiempo de ejecucion: " << tiempo_segundos << " segundos." << '\n';

    delete[] arr; 

    return 0;
}
