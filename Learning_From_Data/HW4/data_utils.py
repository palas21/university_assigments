import numpy as np
import pickle
np.random.seed(42)

def load_cifar10_batch(file_path):
    with open(file_path, 'rb') as f:
        data_dict = pickle.load(f, encoding='bytes')
        images = data_dict[b'data']
        labels = data_dict[b'labels']
    return images, labels

def load_cifar10_data(data_dir):
    images_train = []
    labels_train = []
    for i in range(1, 6):
        file_path = data_dir + '/data_batch_' + str(i)
        images, labels = load_cifar10_batch(file_path)
        images_train.append(images)
        labels_train.append(labels)
    images_train = np.concatenate(images_train, axis=0)
    labels_train = np.concatenate(labels_train, axis=0)

    file_path = data_dir + '/test_batch'
    images_test, labels_test = load_cifar10_batch(file_path)

    return images_train, labels_train, images_test, np.asarray(labels_test)
