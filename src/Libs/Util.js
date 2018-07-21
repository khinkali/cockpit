const acceptOnlyNumbers = (str) => {
    const pattern = /^\d+$/;
    return pattern.test(str);
};

const parseFloatToString = (n) => {
    if(isNaN(n)) {
        throw new Error("The passed argument is not a number.")
    } else {
        return (n % 1 == 0) ? n + ".0" : n.toString();
    }
};

export {acceptOnlyNumbers, parseFloatToString};