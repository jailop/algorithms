#[derive(Debug)]
struct Node<T: Ord> {
    key: T,
    npl: usize,  // null path length
    left: Option<Box<Node<T>>>,
    right: Option<Box<Node<T>>>,
}

impl<T: Ord> Node<T> {
    fn new(key: T) -> Self {
        Node {
            key: key,
            npl: 0,
            left: None,
            right: None,
        }
    }
}

struct LeftistHeap<T: Ord> {
    root: Option<Box<Node<T>>>,
}

impl<T: Ord + std::fmt::Debug> LeftistHeap<T> {
    fn new() -> Self {
        LeftistHeap { root: None }        
    }

    fn merge_nodes(
        h1: Option<Box<Node<T>>>,
        h2: Option<Box<Node<T>>>
    ) -> Option<Box<Node<T>>> {
        match (h1, h2) {
            (None, h) | (h, None) => h,
            (Some(mut left_node), Some(mut right_node)) => {
                // Putting the node with the less value on the left
                if left_node.key > right_node.key {
                    std::mem::swap(&mut left_node, &mut right_node);
                }
                let right_node_left_npl = npl(&right_node.left);
                left_node.right = Self::merge_nodes(left_node.right.take(), Some(right_node));
                if npl(&left_node.right) > right_node_left_npl {
                    std::mem::swap(&mut left_node.left, &mut left_node.right);
                }
                left_node.npl = npl(&left_node.right) + 1;
                Some(left_node)
            }
        }
    }

    fn insert(&mut self, key: T) {
        let new_node = Some(Box::new(Node::new(key)));
        self.root = Self::merge_nodes(self.root.take(), new_node);
    }

    fn find_min(&mut self) -> Option<&T> {
        self.root.as_ref().map(|node| &node.key)
    }

    fn extract_min(&mut self) {
        if let Some(root) = self.root.take() {
            self.root = Self::merge_nodes(root.left, root.right);
        }
    }

    fn print(&mut self) {
        Self::print_tree(&self.root.take());
    }
    
    fn print_tree(h: &Option<Box<Node<T>>>) {
        match h {
            Some(node) => {
                Self::print_tree(&node.left);
                Self::print_tree(&node.right);
                println!("{:?}", node.key);
            },
            None => {},
        }
    }

} 


fn npl<T: Ord>(node: &Option<Box<Node<T>>>) -> usize {
    match node {
        Some(ref node) => node.npl,
        None => 0,
    }
}

fn main() {
    let mut heap = LeftistHeap::<u8>::new();
    heap.insert(10);
    heap.insert(5);
    heap.insert(15);
    heap.insert(20);
    println!("Minimum: {:?}", heap.find_min());
    heap.extract_min();
    println!("Minimum: {:?}", heap.find_min());
    heap.extract_min();
    println!("Minimum: {:?}", heap.find_min());
    heap.extract_min();
    println!("Minimum: {:?}", heap.find_min());
}
