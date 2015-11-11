from fuel.datasets.mnist import MNIST
from common.plotting import plot_mat


mnist_train = MNIST(("train",), subset=slice(None,50000))
mnist_validation = MNIST(("train",), subset=slice(50000, None))
mnist_test = MNIST(("test",))

print ("We have %d training, %d validation, and %d test examples" % (
    mnist_train.num_examples, mnist_validation.num_examples, mnist_test.num_examples))
print ("The examples are pairs of %s:" % (mnist_train.sources,))
for i, source in enumerate(mnist_train.sources):
    labels = mnist_train.axis_labels[source]
    print ('The source #%d named "%s" is a %dd array with axis: %s' % (
        i, source, len(labels), labels))

#Note that for larger datasets that are loaded into mameory the data_sources field may not exist!
plot_mat(mnist_train.data_sources[0][:1], cmap='gray')
