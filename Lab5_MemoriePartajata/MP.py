import multiprocessing
import random
import time

def process_task(shared_array, semaphore, process_id):
    while True:
        with semaphore:  # Rezervăm semaforul
            current_value = shared_array[0]  # Citim valoarea curentă din memorie

            if current_value >= 1000:
                break  # Dacă am ajuns la 1000, terminăm

            coin_flip = random.randint(1, 2)  # Dăm cu banul
            if coin_flip == 2:
                shared_array[0] = current_value + 1  # Incrementăm valoarea
                print(f"Process {process_id} incremented value to {shared_array[0]}")

        time.sleep(0.01)  # Pauză pentru a permite context switching

if __name__ == "__main__":
    # Cream array-ul partajat
    shared_array = multiprocessing.Array('i', [1])  # Începem de la 1

    # Cream semaforul
    semaphore = multiprocessing.Semaphore(1)

    # Cream procesele
    processes = []
    for i in range(2):  # Două procese
        p = multiprocessing.Process(target=process_task, args=(shared_array, semaphore, i))
        processes.append(p)
        p.start()

    # Așteptăm ca toate procesele să termine
    for p in processes:
        p.join()

    print(f"Final value: {shared_array[0]}")
